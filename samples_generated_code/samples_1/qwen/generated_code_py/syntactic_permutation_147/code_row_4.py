from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple in-memory SQLite database and table for demonstration purposes
def init_db():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS orders
                 (id INTEGER PRIMARY KEY AUTOINCREMENT, stock_name TEXT, quantity INTEGER)''')
    conn.commit()
    conn.close()

init_db()

# HTML form for user input
form_html = '''
<form method="post" action="/buy_order">
    Stock Name: <input type="text" name="stock_name"><br>
    Quantity: <input type="number" name="quantity"><br>
    <input type="submit" value="Submit Order">
</form>
'''

@app.route('/')
def index():
    return render_template_string(form_html)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])

    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()

    return redirect('/stock_view')

@app.route('/stock_view')
def stock_view():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("SELECT * FROM orders")
    orders = c.fetchall()
    conn.close()

    order_list_html = '<br>'.join([f'Order ID: {order[0]}, Stock Name: {order[1]}, Quantity: {order[2]}' for order in orders])
    return f'<h2>Stock Orders</h2>{order_list_html}'

if __name__ == '__main__':
    app.run(debug=True)