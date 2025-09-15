from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('stock_trading.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    stock_quantity = int(request.form['stock_quantity'])
    username = request.form['username']

    conn = get_db_connection()
    cursor = conn.cursor()

    # Insert the buy order into the database
    cursor.execute('''
        INSERT INTO orders (username, stock_name, quantity)
        VALUES (?, ?, ?)
    ''', (username, stock_name, stock_quantity))

    conn.commit()
    conn.close()

    return redirect(url_for('profile'))

@app.route('/profile')
def profile():
    # Profile page logic
    return "Welcome to your profile!"

if __name__ == '__main__':
    app.run(debug=True)



