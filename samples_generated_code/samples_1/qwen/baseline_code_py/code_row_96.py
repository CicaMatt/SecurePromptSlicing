from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    stock_quantity = int(request.form['stock_quantity'])
    username = 'example_user'  # Assume username is predefined or retrieved from session

    conn = sqlite3.connect('database.db')
    c = conn.cursor()

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