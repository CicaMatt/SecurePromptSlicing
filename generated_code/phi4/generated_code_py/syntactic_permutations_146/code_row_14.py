from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('stocks.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])
    username = request.form['username']

    if not stock_name or quantity <= 0:
        return "Invalid input", 400

    conn = get_db_connection()
    conn.execute('INSERT INTO buy_orders (username, stock_name, quantity) VALUES (?, ?, ?)',
                 (username, stock_name, quantity))
    conn.commit()
    conn.close()

    return redirect(url_for('profile', username=username))

@app.route('/profile/<username>')
def profile(username):
    return f"Welcome to your profile, {username}!"

if __name__ == '__main__':
    # Initialize the database
    conn = get_db_connection()
    conn.execute('''CREATE TABLE IF NOT EXISTS buy_orders (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT NOT NULL,
                        stock_name TEXT NOT NULL,
                        quantity INTEGER NOT NULL
                    )''')
    conn.commit()
    conn.close()

    app.run(debug=True)