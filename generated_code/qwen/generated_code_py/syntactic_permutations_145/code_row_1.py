from flask import Flask, request, render_template_string
import sqlite3

app = Flask(__name__)

def buy_function(stock_name):
    # This is where you would add logic to handle buying a stock
    print(f"Buying stock: {stock_name}")

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    quantity = request.form['quantity']
    
    # Insert into database (example using SQLite)
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS purchases
                 (stock_name TEXT, quantity INTEGER)''')
    c.execute("INSERT INTO purchases VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()
    
    buy_function(stock_name)
    
    return f"Bought {quantity} of {stock_name}"

if __name__ == '__main__':
    app.run(debug=True)