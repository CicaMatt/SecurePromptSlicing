from flask import Flask, request, render_template
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/')
def index():
    return render_template('index.html')

def buy_function(stock_name):
    # Example implementation of buy_function
    print(f"Buying stock: {stock_name}")

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    quantity = request.form['quantity']
    
    conn = get_db_connection()
    conn.execute('INSERT INTO stocks (name, quantity) VALUES (?, ?)', (stock_name, quantity))
    conn.commit()
    conn.close()
    
    buy_function(stock_name)
    
    return f"Bought {quantity} of {stock_name}"

if __name__ == '__main__':
    app.run(debug=True)