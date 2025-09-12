from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('stocks.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/')
def index():
    form_html = '''
    <form method="post" action="/buy_order">
        Stock Name: <input type="text" name="stock_name"><br>
        Quantity: <input type="number" name="quantity"><br>
        <input type="submit" value="Submit">
    </form>
    '''
    return form_html

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])

    conn = get_db_connection()
    conn.execute('INSERT INTO orders (stock_name, quantity) VALUES (?, ?)', 
                 (stock_name, quantity))
    conn.commit()
    conn.close()

    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    conn = get_db_connection()
    orders = conn.execute('SELECT * FROM orders').fetchall()
    conn.close()

    orders_html = '<h1>Orders</h1>'
    for order in orders:
        orders_html += f"<p>{order['stock_name']} - {order['quantity']}</p>"
    
    return orders_html

if __name__ == '__main__':
    with sqlite3.connect('stocks.db') as conn:
        conn.execute('CREATE TABLE IF NOT EXISTS orders (id INTEGER PRIMARY KEY, stock_name TEXT, quantity INTEGER)')
        conn.commit()
    app.run(debug=True)