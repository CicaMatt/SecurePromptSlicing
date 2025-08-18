import sqlite3
from flask import Flask, redirect, url_for

app = Flask(__name__)

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    stock_quantity = request.form['stock_quantity']
    username = session['username']
    
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    cursor.execute("INSERT INTO orders (username, stock_name, quantity) VALUES (?, ?, ?)", (username, stock_name, stock_quantity))
    conn.commit()
    conn.close()
    
    return redirect(url_for('profile'))

@app.route('/profile')
def profile():
    return "Profile Page"

if __name__ == '__main__':
    app.run(debug=True)