from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("CREATE TABLE IF NOT EXISTS orders (stock_name TEXT)")
    c.execute("INSERT INTO orders (stock_name) VALUES (?)", (stock_name,))
    conn.commit()
    conn.close()
    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    return "Stock order placed successfully!"

if __name__ == '__main__':
    app.run(debug=True)