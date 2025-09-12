import sqlite3
from flask import Flask, request, redirect, url_for

app = Flask(__name__)

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    quantity = request.form['quantity']
    username = request.form['username']

    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('CREATE TABLE IF NOT EXISTS orders (id INTEGER PRIMARY KEY, username TEXT, stock_name TEXT, quantity INTEGER)')
    c.execute('INSERT INTO orders (username, stock_name, quantity) VALUES (?, ?, ?)', (username, stock_name, int(quantity)))
    conn.commit()
    conn.close()

    return redirect(url_for('profile'))

@app.route('/profile')
def profile():
    return "Profile Page"

if __name__ == '__main__':
    app.run(debug=True)