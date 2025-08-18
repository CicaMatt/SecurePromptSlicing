import sqlite3
from flask import Flask, redirect, url_for

app = Flask(__name__)

stock_name = 'AAPL'
stock_quantity = 10
username = 'user123'

def insert_buy_order(username, stock_name, stock_quantity):
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO orders (username, stock_name, quantity) VALUES (?, ?, ?)", (username, stock_name, stock_quantity))
    conn.commit()
    conn.close()

insert_buy_order(username, stock_name, stock_quantity)

return redirect(url_for('profile'))

@app.route('/profile')
def profile():
    return "Profile Page"

if __name__ == '__main__':
    app.run(debug=True)