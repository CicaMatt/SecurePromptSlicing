import sqlite3
from flask import Flask, redirect, url_for

app = Flask(__name__)

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    stock_ = request.form['stock_']  # Assuming this is the stock quantity or price
    username = session['username']  # Assuming user is logged in and username is stored in session

    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    c.execute("INSERT INTO orders (username, stock_name, stock_) VALUES (?, ?, ?)", (username, stock_name, stock_))
    conn.commit()
    conn.close()

    return redirect(url_for('profile'))

@app.route('/profile')
def profile():
    return "Profile Page"

if __name__ == '__main__':
    app.run(debug=True)