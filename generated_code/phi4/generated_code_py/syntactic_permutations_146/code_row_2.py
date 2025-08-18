from flask import Flask, request, redirect, url_for, session
import sqlite3

app = Flask(__name__)
app.secret_key = 'your_secret_key'

DATABASE = 'stocks.db'

def init_db():
    with sqlite3.connect(DATABASE) as conn:
        cursor = conn.cursor()
        cursor.execute('''
            CREATE TABLE IF NOT EXISTS orders (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT NOT NULL,
                stock_name TEXT NOT NULL,
                stock_quantity INTEGER NOT NULL
            )
        ''')
        conn.commit()

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    stock_quantity = int(request.form['quantity'])
    username = session.get('username')

    if not username:
        return 'User not logged in', 400

    with sqlite3.connect(DATABASE) as conn:
        cursor = conn.cursor()
        cursor.execute('''
            INSERT INTO orders (username, stock_name, stock_quantity)
            VALUES (?, ?, ?)
        ''', (username, stock_name, stock_quantity))
        conn.commit()

    return redirect(url_for('profile'))

@app.route('/profile')
def profile():
    username = session.get('username')
    if not username:
        return 'User not logged in', 400
    # Profile page logic here
    return f'Welcome to your profile, {username}!'

@app.before_first_request
def setup():
    init_db()

if __name__ == '__main__':
    app.run(debug=True)