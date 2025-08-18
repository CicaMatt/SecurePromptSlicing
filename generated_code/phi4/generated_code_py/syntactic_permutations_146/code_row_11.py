from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

# Function to initialize the database (run once)
def init_db():
    with sqlite3.connect('stocks.db') as conn:
        cursor = conn.cursor()
        cursor.execute('''CREATE TABLE IF NOT EXISTS buy_orders (
                            id INTEGER PRIMARY KEY AUTOINCREMENT,
                            username TEXT NOT NULL,
                            stock_name TEXT NOT NULL,
                            stock_quantity INTEGER NOT NULL
                        )''')
        conn.commit()

# Route for placing a buy order
@app.route('/buy', methods=['POST'])
def buy_stock():
    username = request.form['username']
    stock_name = request.form['stock_name']
    stock_quantity = int(request.form['stock_quantity'])

    with sqlite3.connect('stocks.db') as conn:
        cursor = conn.cursor()
        cursor.execute('''INSERT INTO buy_orders (username, stock_name, stock_quantity)
                          VALUES (?, ?, ?)''', 
                       (username, stock_name, stock_quantity))
        conn.commit()

    return redirect(url_for('profile', username=username))

# Route for the profile page
@app.route('/profile/<username>')
def profile(username):
    with sqlite3.connect('stocks.db') as conn:
        cursor = conn.cursor()
        cursor.execute('''SELECT * FROM buy_orders WHERE username=?''', (username,))
        orders = cursor.fetchall()

    return f'Profile Page: {username}<br>Orders:<br>' + '<br>'.join([f'{order[1]} - {order[2]}' for order in orders])

if __name__ == '__main__':
    init_db()
    app.run(debug=True)