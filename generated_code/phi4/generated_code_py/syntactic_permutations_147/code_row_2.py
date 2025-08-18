from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Initialize SQLite database and create table if not exists
def init_db():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS orders 
                 (id INTEGER PRIMARY KEY AUTOINCREMENT, stock_name TEXT, quantity INTEGER)''')
    conn.commit()
    conn.close()

@app.route('/buy', methods=['GET'])
def buy_order_form():
    return render_template_string('''
        <form action="/buy_order" method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Submit">
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

    return redirect('/stock_view')

@app.route('/stock_view', methods=['GET'])
def stock_view():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("SELECT * FROM orders")
    orders = c.fetchall()
    conn.close()

    output = '<h1>Stock Orders</h1>'
    for order in orders:
        output += f'<p>ID: {order[0]}, Stock Name: {order[1]}, Quantity: {order[2]}</p>'

    return output

if __name__ == '__main__':
    init_db()
    app.run(debug=True)