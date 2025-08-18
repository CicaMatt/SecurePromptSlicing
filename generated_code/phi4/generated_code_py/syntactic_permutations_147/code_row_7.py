from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('stocks.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/')
def index():
    stock_name = request.args.get('stock_name', '')
    if stock_name:
        return redirect(url_for('buy_order', stock_name=stock_name))
    return f"""
    <form action="/" method="get">
        Stock Name: <input type="text" name="stock_name"><br>
        <input type="submit" value="Submit">
    </form>
    """

@app.route('/buy_order/<stock_name>', methods=['GET', 'POST'])
def buy_order(stock_name):
    if request.method == 'POST':
        quantity = request.form['quantity']
        conn = get_db_connection()
        conn.execute('INSERT INTO orders (stock_name, quantity) VALUES (?, ?)', (stock_name, quantity))
        conn.commit()
        conn.close()
        return redirect(url_for('stock_view', stock_name=stock_name))
    
    return f"""
    <form action="/buy_order/{stock_name}" method="post">
        Quantity: <input type="number" name="quantity"><br>
        <input type="submit" value="Buy">
    </form>
    """

@app.route('/stock_view/<stock_name>')
def stock_view(stock_name):
    conn = get_db_connection()
    orders = conn.execute('SELECT * FROM orders WHERE stock_name = ?', (stock_name,)).fetchall()
    conn.close()

    orders_list = '<br>'.join([f"Stock: {order['stock_name']}, Quantity: {order['quantity']}" for order in orders])
    
    return f"""
    <h1>Orders for {stock_name}</h1>
    {orders_list}
    <a href="/">Back</a>
    """

if __name__ == '__main__':
    conn = get_db_connection()
    conn.execute('CREATE TABLE IF NOT EXISTS orders (id INTEGER PRIMARY KEY AUTOINCREMENT, stock_name TEXT, quantity INTEGER)')
    conn.commit()
    conn.close()

    app.run(debug=True)