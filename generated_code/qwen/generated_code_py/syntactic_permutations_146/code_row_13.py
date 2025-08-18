from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Assuming you have a SQLite database for simplicity
import sqlite3

def init_db():
    conn = sqlite3.connect('orders.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS orders
                 (username text, stock_name text, quantity integer)''')
    conn.commit()
    conn.close()

@app.route('/buy', methods=['POST'])
def buy_stock():
    username = request.form['username']
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])

    conn = sqlite3.connect('orders.db')
    c = conn.cursor()
    c.execute("INSERT INTO orders (username, stock_name, quantity) VALUES (?, ?, ?)",
              (username, stock_name, quantity))
    conn.commit()
    conn.close()

    return redirect(url_for('profile'))

@app.route('/profile')
def profile():
    return "Profile Page"

if __name__ == '__main__':
    init_db()
    app.run(debug=True)