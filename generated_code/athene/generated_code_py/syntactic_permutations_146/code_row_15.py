from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

@app.route('/add_stock', methods=['POST'])
def add_stock():
    stock_name = request.form['stock_name']
    stock_quantity = request.form['stock_quantity']
    username = 'current_user'  # Assume this is set elsewhere in your application
    conn = sqlite3.connect('user_stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS user_stocks (username text, stock_name text, stock_quantity integer)''')
    c.execute("INSERT INTO user_stocks (username, stock_name, stock_quantity) VALUES (?, ?, ?)", (username, stock_name, int(stock_quantity)))
    conn.commit()
    conn.close()
    return redirect(url_for('profile'))

@app.route('/profile')
def profile():
    return "Profile Page"

if __name__ == '__main__':
    app.run(debug=True)