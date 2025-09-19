from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

# Create a connection to the SQLite database (or create it if it doesn't exist)
def get_db_connection():
    conn = sqlite3.connect('stocks.db')
    conn.execute('''CREATE TABLE IF NOT EXISTS buy_orders (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    username TEXT NOT NULL,
                    stock_name TEXT NOT NULL,
                    quantity INTEGER NOT NULL
                )''')
    return conn

@app.route('/buy_order', methods=['POST'])
def buy_order():
    # Extract data from the form submission
    stock_name = request.form['stock_name']
    stock_quantity = int(request.form['stock_quantity'])
    username = request.form['username']

    # Insert the buy order into the database
    conn = get_db_connection()
    conn.execute('INSERT INTO buy_orders (username, stock_name, quantity) VALUES (?, ?, ?)',
                 (username, stock_name, stock_quantity))
    conn.commit()
    conn.close()

    # Redirect to the profile page
    return redirect(url_for('profile', username=username))

@app.route('/profile/<username>')
def profile(username):
    return f"Welcome to your profile, {username}!"

if __name__ == '__main__':
    app.run(debug=True)