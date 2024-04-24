import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, jsonify
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Show portfolio of stocks
@app.route("/")
@login_required
def index():

    # Get the current user's ID
    user_id = session["user_id"]

    # Get user information from the database for the current user
    user = db.execute("SELECT * FROM users WHERE id = ?", user_id)

    # Get current user's username
    username = user[0]["username"]

    # Get current user's cash total
    cash = user[0]["cash"]

    # Get a list of dictionaries (each one representing a different stock type) including the symbol, sum of shares, and stock prices of the stocks
    database = db.execute("SELECT symbol, SUM(shares) AS shares, stock_price FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", user_id)

    # Get total value of all stocks owned
    total = 0
    for row in database:
        total = total + (row["shares"] * row["stock_price"])
    total = total + cash

    # Display a table of the stocks the current user owns (and total value of their stocks and cash)
    return render_template("index.html", database=database, username=username, cash=cash, total=total)


# Buy shares of stock
@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():

    # GET (as by clicking a link or via redirect)
    if request.method == "GET":
        return render_template("buy.html")

    # POST (as by submitting a form via POST)
    else:
        # Get the current user's ID
        user_id = session["user_id"]

        # Determine the transaction's current date and time (formatted to sqlite3's datetime format)
        date_time = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        # Get user's stock symbol and number of shares to buy
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Ensure stock's symbol was submitted
        if not symbol:
            return apology("Must provide stock's symbol", 400)

        # Ensure stock's symbol is valid
        if not lookup(symbol):
            return apology("Stock's symbol does not exist", 400)

        # Ensure number of shares was submitted
        if not shares:
            return apology("Must provide number of shares to buy", 400)

        # Ensure number of shares to buy is a positive integer
        try:
            shares = int(shares)
            if shares <= 0:
                raise ValueError
        except ValueError:
            return apology("Number of shares must be a positive integer", 400)

        # Get the stock's symbol (correctly formatted) and price (per share)
        symbol = lookup(symbol)["symbol"]
        price = lookup(symbol)["price"]

        # Calculate the total transactional value of shares bought
        transaction_value = price * shares

        # Check how much cash the user has in their account
        usercash = db.execute("SELECT * FROM users WHERE id = ?", user_id)
        usercash = float(usercash[0]["cash"])

        # Check if user has enough cash in their acoount to buy these shares of stocks
        if usercash < transaction_value:
            return apology("Not enough cash to buy these stocks", 400)

        # Calculate how much cash the user has left in their account after buying the stocks
        cashleft = usercash - transaction_value

        # Update the user database with how much cash the current user has left
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cashleft, user_id)

        # Add transaction data into the transaction database
        db.execute("INSERT INTO transactions (user_id, symbol, stock_price, shares, date_time) VALUES(?, ?, ?, ?, ?)", user_id, symbol, price, shares, date_time)

        # Alerts the user they have successfully bought the stocks
        flash(f"Bought {symbol} stocks!")

        # Redirects user to the homepage
        return redirect("/")


# Show history of transactions
@app.route("/history")
@login_required
def history():

    # Get the current user's ID
    user_id = session["user_id"]

    # Get the database of transactions for the current user
    database = db.execute("SELECT * FROM transactions WHERE user_id = ?", user_id)

    # Modify the database in reverse order
    database.reverse()

    # Directs user to the transaction history page
    return render_template("history.html", database=database)


# Log user in
@app.route("/login", methods=["GET", "POST"])
def login():

    # Forget any user_id
    session.clear()

    # GET (as by clicking a link or via redirect)
    if request.method == "GET":
        return render_template("login.html")

    # POST (as by submitting a form via POST)
    else:
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("Must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("Must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("Invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")


# Log user out
@app.route("/logout")
def logout():

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


# Get stock quote
@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():

    # GET (as by clicking a link or via redirect)
    if request.method == "GET":
        return render_template("quote.html")

    # POST (as by submitting a form via POST)
    else:

        # Get user's stock symbol requested
        symbol = request.form.get("symbol")

        # Ensure stock's symbol was submitted
        if not symbol:
            return apology("Must provide stock's symbol", 400)

        # Ensure stock's symbol is valid
        if not lookup(symbol):
            return apology("Stock's symbol does not exist", 400)

        # Get the stock's symbol (correctly formatted) and price
        stocksymbol = lookup(symbol)["symbol"]
        price = lookup(symbol)["price"]

        # Displays the selected stock and price quote
        return render_template("quoted.html", price=price, symbol=stocksymbol)


# Register user
@app.route("/register", methods=["GET", "POST"])
def register():

    # Forget any user_id
    session.clear()

    # GET (as by clicking a link or via redirect)
    if request.method == "GET":
        return render_template("register.html")

    # POST (as by submitting a form via POST)
    else:

        # Retrieve username, password, and password confirmation submitted in registration form
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure username was submitted
        if not username:
            return apology("Must provide username", 400)

        # Ensure password was submitted
        if not password:
            return apology("Must provide password", 400)

        # Ensure password confirmation was submitted
        if not confirmation:
            return apology("Must provide password confirmation", 400)

        # Ensure password and confirmation both match
        if password != confirmation:
            return apology("Passwords do not match", 400)

        # Add newly registered user into the database if not already a registered user (username column is unique)
        try:
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, generate_password_hash(password))
        except:
            return apology("User already exists", 400)

        # Remember the user after registering
        session["user_id"] = db.execute("SELECT * FROM users WHERE username = ?", username)[0]["id"]

        # Redirect to homepage
        return redirect("/")


# Sell shares of stock
@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():

    # GET (as by clicking a link or via redirect)
    if request.method == "GET":

        # Get current user's ID
        user_id = session["user_id"]

        # Get list of dictionaries of all stocks (symbols) where the current user owns stocks with positive values
        symbols = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", user_id)

        # Brings user to selling stocks page (user can select to sell stocks from those they currently own)
        return render_template("sell.html", symbols=symbols)

    # POST (as by submitting a form via POST)
    else:
        # Get the current user's ID
        user_id = session["user_id"]

        # Determine the transaction's current date and time (formatted to sqlite3's datetime format)
        date_time = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        # Get user's stock symbol and number of shares to sell
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Ensure stock's symbol was submitted
        if not symbol:
            return apology("Must provide stock's symbol", 400)

        # Ensure stock's symbol is valid
        if not lookup(symbol):
            return apology("Stock's symbol does not exist", 400)

        # Ensure number of shares was submitted
        if not shares:
            return apology("Must provide number of shares to buy", 400)

        # Ensure number of shares to sell is a positive integer
        try:
            shares = int(shares)
            if shares <= 0:
                raise ValueError
        except ValueError:
            return apology("Number of shares must be a positive integer", 400)

        # Get the stock's symbol (correctly formatted) and price (per share)
        symbol = lookup(symbol)["symbol"]
        price = lookup(symbol)["price"]

        # Ensure the current user has enough of the stock selected to sell
        user_shares = db.execute("SELECT SUM(shares) AS shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol", user_id, symbol)
        if not user_shares:
            return apology("User does not own any shares of this stock", 400)
        if shares > user_shares[0]["shares"]:
            return apology("Not enough shares of this stock to sell", 400)

        # Calculate the total transactional value of shares to sell
        transaction_value = price * shares

        # Check how much cash the user has in their account
        usercash = db.execute("SELECT * FROM users WHERE id = ?", user_id)
        usercash = float(usercash[0]["cash"])

        # Calculate how much cash the user will have in their account after selling the stocks
        cashupdated = usercash + transaction_value

        # Update the user database with how much cash the current will have after selling the stocks
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cashupdated, user_id)

        # Add transaction data into the transaction database
        db.execute("INSERT INTO transactions (user_id, symbol, stock_price, shares, date_time) VALUES(?, ?, ?, ?, ?)", user_id, symbol, price, (-1)*shares, date_time)

        # Alerts the user they have successfully bought the stocks
        flash(f"Sold {symbol} stocks!")

        # Redirects user to the homepage
        return redirect("/")

# Add cash to user's account
@app.route("/addcash", methods=["GET", "POST"])
@login_required
def addcash():

    # GET (as by clicking a link or via redirect)
    if request.method == "GET":
        return render_template("addcash.html")

    # POST (as by submitting a form via POST)
    else:
        # Get the current user's ID
        user_id = session["user_id"]

        # Get cash to be added to the account from the user
        addcash = request.form.get("cash")

        # Ensure cash to be added is a positive number
        try:
            addcash = float(addcash)
            if addcash <= 0:
                raise ValueError
        except ValueError:
            return apology("Cash to add must be a positive number", 400)

        # Get the amount of cash in the user's account
        cash = db.execute("SELECT * FROM users WHERE id = ?", user_id)
        cash = cash[0]["cash"]

        # Add cash to add to the current amount of cash in the user's account
        totalcash = cash + addcash

        # Update the value of cash in the user's account
        db.execute("UPDATE users SET cash = ? WHERE id = ?", totalcash, user_id)

        # Redirects user to the homepage
        return redirect("/")


