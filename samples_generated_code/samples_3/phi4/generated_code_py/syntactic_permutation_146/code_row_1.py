import sqlite3
from flask import Flask, request, redirect, url_for

app = Flask(__name__)

def create_db():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS buy_orders (
                 id INTEGER PRIMARY KEY AUTOINCREMENT,
                 username TEXT NOT NULL,
                 stock_name TEXT NOT NULL,
                 quantity INTEGER NOT NULL)''')
    conn.commit()
    conn.close()

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form.get('stock_name')
    stock_quantity = int(request.form.get('quantity'))
    username = request.form.get('username')

    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO buy_orders (username, stock_name, quantity) VALUES (?, ?, ?)",
              (username, stock_name, stock_quantity))
    conn.commit()
    conn.close()

    return redirect(url_for('profile'))

@app.route('/profile')
def profile():
    return "Welcome to your profile!"

if __name__ == '__main__':
    create_db()
    app.run(debug=True)