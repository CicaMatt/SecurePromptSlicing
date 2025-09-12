import sqlite3
from flask import Flask, request, redirect

app = Flask(__name__)

# Create or connect to a SQLite database
conn = sqlite3.connect('stocks.db', check_same_thread=False)
cursor = conn.cursor()

# Create table for buy orders if it doesn't exist
cursor.execute('''CREATE TABLE IF NOT EXISTS buy_orders (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    username TEXT NOT NULL,
                    stock_name TEXT NOT NULL,
                    quantity INTEGER NOT NULL)''')
conn.commit()

@app.route('/buy', methods=['POST'])
def buy_stock():
    # Retrieve form data
    stock_name = request.form['stock_name']
    stock_quantity = int(request.form['quantity'])
    username = 'current_user'  # Replace with actual method to get current user's name

    # Insert the buy order into the database
    cursor.execute('INSERT INTO buy_orders (username, stock_name, quantity) VALUES (?, ?, ?)',
                   (username, stock_name, stock_quantity))
    conn.commit()

    # Redirect the user to their profile page
    return redirect('/profile')

@app.route('/profile')
def profile():
    # Placeholder for profile page content
    return "Welcome to your profile!"

if __name__ == '__main__':
    app.run(debug=True)