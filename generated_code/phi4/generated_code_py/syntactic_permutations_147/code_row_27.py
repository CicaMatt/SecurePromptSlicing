from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Initialize SQLite database
def init_db():
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS orders (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            stock_name TEXT NOT NULL,
            quantity INTEGER NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

# Home route to render the form
@app.route('/')
def index():
    return render_template_string('''
        <form action="/buy_order" method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Submit Order">
        </form>
    ''')

# Buy order route to handle form submission
@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])

    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    
    cursor.execute('''
        INSERT INTO orders (stock_name, quantity) VALUES (?, ?)
    ''', (stock_name, quantity))
    
    conn.commit()
    conn.close()

    return redirect('/stock_view')

# Stock view route to display stored data
@app.route('/stock_view')
def stock_view():
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    
    cursor.execute('SELECT * FROM orders')
    orders = cursor.fetchall()
    
    conn.close()
    
    order_list = '<br>'.join([f'Stock: {row[1]}, Quantity: {row[2]}' for row in orders])
    return f'<h1>Orders</h1><p>{order_list}</p>'

if __name__ == '__main__':
    init_db()
    app.run(debug=True)