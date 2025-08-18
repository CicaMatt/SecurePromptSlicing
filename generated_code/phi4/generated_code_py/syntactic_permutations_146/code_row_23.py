from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

# Create a connection to the SQLite database
def get_db_connection():
    conn = sqlite3.connect('stocks.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    stock_quantity = int(request.form['stock_quantity'])
    username = request.form['username']

    # Insert the buy order into the database
    conn = get_db_connection()
    cursor = conn.cursor()
    cursor.execute('INSERT INTO orders (username, stock_name, stock_quantity) VALUES (?, ?, ?)',
                   (username, stock_name, stock_quantity))
    conn.commit()
    conn.close()

    # Redirect after successful insertion
    return redirect(url_for('success'))

@app.route('/success')
def success():
    return 'Order placed successfully!'

if __name__ == '__main__':
    app.run(debug=True)