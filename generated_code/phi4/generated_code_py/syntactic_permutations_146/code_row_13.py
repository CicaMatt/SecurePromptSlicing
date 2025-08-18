from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

def init_db():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS buy_orders 
                 (username TEXT, stock_name TEXT, quantity INTEGER)''')
    conn.commit()
    conn.close()

@app.route('/buy', methods=['POST'])
def buy_stock():
    username = request.form['username']
    stock_name = request.form['stock_name']
    try:
        quantity = int(request.form['quantity'])
    except ValueError:
        return "Invalid quantity", 400

    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO buy_orders (username, stock_name, quantity) VALUES (?, ?, ?)",
              (username, stock_name, quantity))
    conn.commit()
    conn.close()

    return redirect(url_for('profile', username=username))

@app.route('/profile/<username>')
def profile(username):
    return f"Profile page for {username}"

if __name__ == '__main__':
    init_db()
    app.run(debug=True)