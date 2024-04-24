/* SQL query to create a new transaction data table for the finance web application */
/* Each transaction shows the user_id, stock (symbol), bought vs sold, stock price, number of shares, total price, and date/time */
CREATE TABLE transactions (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    user_id INTEGER,
    symbol TEXT NOT NULL,
    bought_sold TEXT NOT NULL,
    stock_price NUMERIC NOT NULL,
    shares NUMERIC NOT NULL,
    total_price NUMERIC NOT NULL,
    date_time TIMESTAMP NOT NULL,
    FOREIGN KEY(user_id) REFERENCES users(id)
);

