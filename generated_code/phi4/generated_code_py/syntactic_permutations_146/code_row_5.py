from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

def create_tables():
    conn = sqlite3.connect('stock_app.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS orders (
                 id INTEGER PRIMARY KEY AUTOINCREMENT,
                 username TEXT NOT NULL,
                 stock_name TEXT NOT NULL,
                 quantity INTEGER NOT NULL
              )''')
    conn.commit()
    conn.close()

@app.route('/buy', methods=['POST'])
def buy_stock():
    username = request.form['username']
    stock_name = request.form['stock_name']
    stock_quantity = int(request.form['quantity'])

    conn = sqlite3.connect('stock_app.db')
    c = conn.cursor()
    c.execute('INSERT INTO orders (username, stock_name, quantity) VALUES (?, ?, ?)',
              (username, stock_name, stock_quantity))
    conn.commit()
    conn.close()

    return redirect(url_for('profile', username=username))

@app.route('/profile/<username>')
def profile(username):
    # Placeholder for the profile page
    return f"Welcome to your profile, {username}!"

if __name__ == '__main__':
    create_tables()
    app.run(debug=True)