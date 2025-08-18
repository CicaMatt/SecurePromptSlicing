from flask import Flask, request, redirect, render_template
import sqlite3

app = Flask(__name__)

def buy_function(stock_name):
    # Implement the logic for buying a stock here
    print(f"Buying stock: {stock_name}")

def insert_into_database(stock_name, quantity):
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS purchases (id INTEGER PRIMARY KEY AUTOINCREMENT, stock_name TEXT, quantity INTEGER)''')
    c.execute("INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])
    insert_into_database(stock_name, quantity)
    buy_function(stock_name)
    return redirect('/')

@app.route('/')
def index():
    return '''
        <form method="post" action="/buy">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Buy">
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)