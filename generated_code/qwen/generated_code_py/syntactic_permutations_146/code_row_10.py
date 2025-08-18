from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

@app.route('/place_order', methods=['POST'])
def place_order():
    stock_name = request.form['stock_name']
    stock_quantity = request.form['stock_quantity']
    username = request.form['username']

    conn = sqlite3.connect('database.db')
    c = conn.cursor()

    c.execute('''CREATE TABLE IF NOT EXISTS orders
                 (username TEXT, stock_name TEXT, quantity INTEGER)''')

    c.execute("INSERT INTO orders (username, stock_name, quantity) VALUES (?, ?, ?)",
              (username, stock_name, stock_quantity))

    conn.commit()
    conn.close()

    return redirect(url_for('profile'))

@app.route('/profile')
def profile():
    return "Profile Page"

if __name__ == '__main__':
    app.run(debug=True)