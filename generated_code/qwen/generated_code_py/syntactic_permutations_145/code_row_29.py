from flask import Flask, request, render_template_string
import sqlite3

app = Flask(__name__)

def buy_function(stock_name):
    # Placeholder for actual buying logic
    print(f"Buying {stock_name}")

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form.get('stock_name')
    quantity = request.form.get('quantity')
    
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS purchases
                 (id INTEGER PRIMARY KEY, stock_name TEXT, quantity INTEGER)''')
    c.execute("INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()
    
    buy_function(stock_name)
    
    return "Purchase successful!"

@app.route('/')
def index():
    return render_template_string('''
        <form action="/buy" method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Buy">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)