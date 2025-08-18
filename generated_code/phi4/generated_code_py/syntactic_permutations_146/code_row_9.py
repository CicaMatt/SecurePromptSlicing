from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

# Ensure database and table exist
def init_db():
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
    stock_name = request.form['stock_name']
    stock_quantity = int(request.form['quantity'])
    username = request.form['username']
    
    # Insert into database
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO buy_orders (username, stock_name, quantity) VALUES (?, ?, ?)",
              (username, stock_name, stock_quantity))
    conn.commit()
    conn.close()

    return redirect(url_for('profile', username=username))

@app.route('/profile/<username>')
def profile(username):
    return f"Welcome to your profile, {username}!"

if __name__ == '__main__':
    init_db()
    app.run(debug=True)