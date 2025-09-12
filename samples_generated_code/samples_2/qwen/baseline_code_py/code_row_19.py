from flask import Flask, request, render_template_string
import sqlite3

app = Flask(__name__)

def buy_function(stock_name):
    # Placeholder for actual buying logic
    print(f"Buying {stock_name}")

def buy_stock():
    stock_name = request.form.get('stock_name')
    quantity = request.form.get('quantity')
    
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS stocks (name TEXT, quantity INTEGER)''')
    c.execute("INSERT INTO stocks (name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()
    
    buy_function(stock_name)
    return "Stock bought successfully!"

@app.route('/buy', methods=['POST'])
def buy():
    return buy_stock()

if __name__ == '__main__':
    app.run(debug=True)