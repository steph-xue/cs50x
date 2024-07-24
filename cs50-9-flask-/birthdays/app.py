# The birthdays flask application allows the user to input a new user's birthday (name, birth month, birth day) into a form
# The application displays a table of all users' names and birthdays

import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

# Ensure responses are not cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Renders webpage with form to input a new user's birthday and a table of all users' birthdays
@app.route("/", methods=["GET", "POST"])
def index():

    # POST - Upon submission of user's entry in the form (name, birth month, birth day), add the user's entry into the birthdays database
    if request.method == "POST":

        # Validate name
        name = request.form.get("name")
        if not name:
            return redirect("/")

        # Validate month (number from 1-12)
        month = request.form.get("month")
        if not month:
            return redirect("/")
        try:
            month = int(month)
        except ValueError:
            return redirect("/")
        if month < 0 or month > 12:
            return redirect("/")

        # Validate day (number from 1-31)
        day = request.form.get("day")
        if not day:
            return redirect("/")
        try:
            day = int(day)
        except ValueError:
            return redirect("/")
        if day < 0 or day > 31:
            return redirect("/")

        # Insert data into birthdays database once all checks are passed
        db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, month, day)
        return redirect("/")

    # GET - Displays webpage with form to input a new user's birthday and a table of all updated users' birthdays
    else:
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("birthdays.html", birthdays=birthdays)


# Removes birthday from the database if button is clicked on to remove a user's birthday
@app.route("/remove", methods=["POST"])
def remove():
    id = request.form.get("id1")
    if id:
        db.execute("DELETE FROM birthdays WHERE id = ?", id)
    return redirect("/")


# Brings up editing page if button is clicked on to edit a selected user's birthday
@app.route("/edit", methods=["POST"])
def edit():
    id = request.form.get("id2")
    if id:
        birthday = db.execute("SELECT * FROM birthdays WHERE id = ?", id)
        return render_template("edit.html", birthday=birthday[0])
    return redirect("/")


# Can make edits to name, birth month, and birth day in the birthday database for a particular user selected
@app.route("/makeedit", methods=["POST"])
def makeedit():

    # Get id of the user selected
    id = request.form.get("editid")

    # Edit name in database for the user
    name = request.form.get("editname")
    if name:
        db.execute("UPDATE birthdays SET name = ? WHERE id = ?", name, id)

    # Validate month (number from 1-12) and edit month in database for the user
    month = request.form.get("editmonth")
    if month:
        try:
            month = int(month)
            if month < 1 or month > 12:
                raise ValueError
        except ValueError:
            return redirect("/makeedit")
        db.execute("UPDATE birthdays SET month = ? WHERE id = ?", month, id)

    # Validate day (number from 1-31) and edit day in database for the user
    day = request.form.get("editday")
    if day:
        try:
            day = int(day)
            if day < 1 or day > 31:
                raise ValueError
        except ValueError:
            return redirect("/makeedit")
        db.execute("UPDATE birthdays SET day = ? WHERE id = ?", day, id)


    # After making the edits, redirects to the homepage with all updated birthday data entries displays
    return redirect("/")


