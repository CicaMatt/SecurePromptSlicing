import sqlite3
from flask import Flask, request, redirect, url_for

app = Flask(__name__)

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    stock_quantity = int(request.form['stock_quantity'])
    username = request.form['username']

    conn = sqlite3.connect('trading.db')
    cursor = conn.cursor()
    cursor.execute('INSERT INTO orders (username, stock_name, quantity, order_type) VALUES (?, ?, ?, ?)', 
                   (username, stock_name, stock_quantity, 'buy'))
    conn.commit()
    conn.close()

    return redirect(url_for('profile'))

@app.route('/profile')
def profile():
    return "Profile Page"

if __name__ == '__main__':
    app.run(debug=True)