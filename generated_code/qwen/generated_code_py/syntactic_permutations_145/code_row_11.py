from flask import Flask, request, render_template_string
import sqlite3

app = Flask(__name__)

def buy_function(stock_name):
    # Simulate buying a stock
    print(f"Buying stock: {stock_name}")

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO stocks (name) VALUES (?)", (stock_name,))
    conn.commit()
    conn.close()
    buy_function(stock_name)
    return "Stock bought successfully!"

@app.route('/')
def index():
    return render_template_string('''
        <form action="/buy" method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            <input type="submit" value="Buy">
        </form>
    ''')

if __name__ == '__main__':
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS stocks
                 (id INTEGER PRIMARY KEY, name TEXT)''')
    conn.commit()
    conn.close()
    app.run(debug=True)