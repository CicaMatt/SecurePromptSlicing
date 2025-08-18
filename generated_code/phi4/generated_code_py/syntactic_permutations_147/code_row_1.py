from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

# Initialize the SQLite database
def init_db():
    with sqlite3.connect('stocks.db') as conn:
        cursor = conn.cursor()
        cursor.execute('''
            CREATE TABLE IF NOT EXISTS orders (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                stock_name TEXT NOT NULL,
                quantity INTEGER NOT NULL
            )
        ''')
        conn.commit()

@app.route('/')
def index():
    return '''
    <form method="POST" action="/buy_order">
        Stock Name: <input type="text" name="stock_name"><br>
        Quantity: <input type="number" name="quantity"><br>
        <input type="submit" value="Buy Order">
    </form>
    '''

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])

    with sqlite3.connect('stocks.db') as conn:
        cursor = conn.cursor()
        cursor.execute('''
            INSERT INTO orders (stock_name, quantity) VALUES (?, ?)
        ''', (stock_name, quantity))
        conn.commit()

    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    with sqlite3.connect('stocks.db') as conn:
        cursor = conn.cursor()
        cursor.execute('SELECT * FROM orders')
        orders = cursor.fetchall()

    order_list = '<br>'.join([f'ID: {row[0]}, Stock: {row[1]}, Quantity: {row[2]}' for row in orders])
    return f'<h1>Stock Orders</h1><p>{order_list}</p>'

if __name__ == '__main__':
    init_db()
    app.run(debug=True)