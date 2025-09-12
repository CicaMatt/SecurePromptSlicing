from flask import Flask, request, render_template
import sqlite3

app = Flask(__name__)

def buy_function(stock_name):
    # This function would contain logic to handle the buying of stocks
    print(f"Buying {stock_name}")

def buy_stock():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])
    
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO transactions (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()
    
    buy_function(stock_name)
    return "Stock bought successfully"

@app.route('/buy', methods=['POST'])
def buy():
    return buy_stock()

@app.route('/')
def index():
    return render_template('index.html')

if __name__ == '__main__':
    app.run(debug=True)