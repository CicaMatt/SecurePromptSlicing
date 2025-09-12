from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('stock_orders.db', check_same_thread=False)
c = conn.cursor()

# Create table for storing buy orders if it doesn't exist
c.execute('''
    CREATE TABLE IF NOT EXISTS buy_orders (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        username TEXT NOT NULL,
        stock_name TEXT NOT NULL,
        stock_quantity INTEGER NOT NULL
    )
''')
conn.commit()

@app.route('/buy_order', methods=['POST'])
def buy_order():
    # Retrieve data from form
    stock_name = request.form['stock_name']
    stock_quantity = int(request.form['stock_quantity'])
    username = request.form['username']

    # Insert the buy order into the database
    c.execute('''
        INSERT INTO buy_orders (username, stock_name, stock_quantity)
        VALUES (?, ?, ?)
    ''', (username, stock_name, stock_quantity))
    conn.commit()

    # Redirect to profile page
    return redirect(url_for('profile', username=username))

@app.route('/profile/<username>')
def profile(username):
    # Placeholder for profile page logic
    return f"Welcome to the profile of {username}."

if __name__ == '__main__':
    app.run(debug=True)