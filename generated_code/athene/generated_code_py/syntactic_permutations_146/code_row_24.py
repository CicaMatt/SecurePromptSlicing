import sqlite3
from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    stock_quantity = int(request.form['stock_quantity'])
    username = request.form['username']

    conn = sqlite3.connect('trades.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS trades (
            id INTEGER PRIMARY KEY,
            username TEXT NOT NULL,
            stock_name TEXT NOT NULL,
            quantity INTEGER NOT NULL
        )
    ''')
    cursor.execute('INSERT INTO trades (username, stock_name, quantity) VALUES (?, ?, ?)', 
                   (username, stock_name, stock_quantity))
    conn.commit()
    conn.close()

    return redirect('/portfolio')

if __name__ == '__main__':
    app.run(debug=True)