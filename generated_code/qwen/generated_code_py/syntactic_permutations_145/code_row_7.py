from flask import Flask, request, render_template_string
import sqlite3

app = Flask(__name__)

def buy_function(stock_name):
    # Placeholder for actual buying logic
    print(f"Buying stock: {stock_name}")

def buy_stock():
    stock_name = request.form.get('stock_name')
    quantity = request.form.get('quantity')
    
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS purchases (stock_name text, quantity integer)''')
    c.execute("INSERT INTO purchases VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()
    
    buy_function(stock_name)
    return "Stock purchased successfully!"

@app.route('/buy', methods=['POST'])
def buy():
    return buy_stock()

if __name__ == '__main__':
    app.run(debug=True)