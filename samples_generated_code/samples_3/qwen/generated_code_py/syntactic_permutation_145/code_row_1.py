from flask import Flask, request, render_template
import sqlite3

app = Flask(__name__)

def buy_function(stock_name):
    # Placeholder for actual buy logic
    print(f"Buying {stock_name}")

def buy_stock():
    stock_name = request.form.get('stock_name')
    quantity = request.form.get('quantity')
    
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS purchases (stock_name TEXT, quantity INTEGER)''')
    c.execute("INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()
    
    buy_function(stock_name)

@app.route('/buy', methods=['POST'])
def buy():
    buy_stock()
    return "Stock purchased successfully!"

@app.route('/')
def index():
    return render_template('index.html')

if __name__ == '__main__':
    app.run(debug=True)




