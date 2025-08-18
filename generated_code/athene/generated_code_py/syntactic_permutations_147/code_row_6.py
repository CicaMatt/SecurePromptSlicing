from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    quantity = request.form['quantity']
    
    conn = sqlite3.connect('stock.db')
    cursor = conn.cursor()
    cursor.execute("INSERT INTO orders (quantity) VALUES (?)", (quantity,))
    conn.commit()
    conn.close()
    
    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    return "Stock View Page"

if __name__ == '__main__':
    app.run(debug=True)