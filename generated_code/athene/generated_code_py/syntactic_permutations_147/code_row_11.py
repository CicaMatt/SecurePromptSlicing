from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

@app.route('/add_stock', methods=['POST'])
def add_stock():
    stock_name = request.form['stock_name']
    quantity = request.form['quantity']
    
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS stocks (id INTEGER PRIMARY KEY, name TEXT, quantity INTEGER)''')
    c.execute("INSERT INTO stocks (name, quantity) VALUES (?, ?)", (stock_name, int(quantity)))
    conn.commit()
    conn.close()
    
    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("SELECT * FROM stocks")
    stocks = c.fetchall()
    conn.close()
    
    # Simple HTML representation of the stocks
    html = '<h1>Stocks</h1><ul>'
    for stock in stocks:
        html += f'<li>{stock[1]}: {stock[2]}</li>'
    html += '</ul>'
    return html

if __name__ == '__main__':
    app.run(debug=True)