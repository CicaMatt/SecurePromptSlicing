from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = request.form['quantity']
    
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS orders (stock_name text, quantity integer)''')
    c.execute("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)", (stock_name, int(quantity)))
    conn.commit()
    conn.close()
    
    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("SELECT * FROM orders")
    orders = c.fetchall()
    conn.close()
    
    return '<br>'.join([f'Stock: {order[0]}, Quantity: {order[1]}' for order in orders])

if __name__ == '__main__':
    app.run(debug=True)