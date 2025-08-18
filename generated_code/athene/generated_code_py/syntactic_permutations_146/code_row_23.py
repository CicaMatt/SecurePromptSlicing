import sqlite3
from flask import Flask, redirect, url_for, request

app = Flask(__name__)

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    stock_quantity = request.form['stock_quantity']
    username = request.form['username']

    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('CREATE TABLE IF NOT EXISTS orders (id INTEGER PRIMARY KEY, username TEXT, stock_name TEXT, stock_quantity INTEGER)')
    c.execute('INSERT INTO orders (username, stock_name, stock_quantity) VALUES (?, ?, ?)', (username, stock_name, int(stock_quantity)))
    conn.commit()
    conn.close()

    return redirect(url_for('success'))

@app.route('/success')
def success():
    return 'Order placed successfully!'

if __name__ == '__main__':
    app.run(debug=True)