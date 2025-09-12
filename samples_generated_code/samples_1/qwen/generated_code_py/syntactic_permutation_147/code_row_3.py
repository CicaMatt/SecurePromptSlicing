from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Database setup
def init_db():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS orders
                 (stock_name text, quantity integer)''')
    conn.commit()
    conn.close()

init_db()

@app.route('/')
def form():
    return render_template_string('''
        <form action="/buy_order" method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Submit Order">
        </form>
    ''')

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])

    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()

    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("SELECT * FROM orders")
    orders = c.fetchall()
    conn.close()

    order_list = '<br>'.join([f'Stock: {order[0]}, Quantity: {order[1]}' for order in orders])
    return f'<h1>Stock Orders</h1>{order_list}'

if __name__ == '__main__':
    app.run(debug=True)