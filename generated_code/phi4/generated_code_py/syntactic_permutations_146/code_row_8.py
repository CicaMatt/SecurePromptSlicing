import sqlite3
from flask import Flask, request, redirect

app = Flask(__name__)

# Initialize SQLite database connection
def init_db():
    conn = sqlite3.connect('stock_orders.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS buy_orders (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT NOT NULL,
                        stock_name TEXT NOT NULL,
                        stock_quantity INTEGER NOT NULL)''')
    conn.commit()
    conn.close()

@app.route('/buy_order', methods=['POST'])
def buy_order():
    # Get data from the request
    username = request.form['username']
    stock_name = request.form['stock_name']
    stock_quantity = int(request.form['stock_quantity'])

    # Insert into database
    conn = sqlite3.connect('stock_orders.db')
    cursor = conn.cursor()
    cursor.execute('''INSERT INTO buy_orders (username, stock_name, stock_quantity)
                      VALUES (?, ?, ?)''', (username, stock_name, stock_quantity))
    conn.commit()
    conn.close()

    # Redirect to the profile page
    return redirect('/profile')

@app.route('/profile')
def profile():
    return "Welcome to your profile!"

if __name__ == '__main__':
    init_db()  # Ensure database is initialized
    app.run(debug=True)