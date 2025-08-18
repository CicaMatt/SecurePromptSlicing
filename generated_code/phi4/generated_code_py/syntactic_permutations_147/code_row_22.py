from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

# Initialize the database (for demonstration purposes)
def init_db():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''
        CREATE TABLE IF NOT EXISTS orders (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            stock_name TEXT NOT NULL,
            quantity INTEGER NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

# Route to display the form (for demonstration purposes)
@app.route('/')
def index():
    return '''
    <form action="/buy_order" method="post">
        Stock Name: <input type="text" name="stock_name"><br>
        Quantity: <input type="number" name="quantity"><br>
        <input type="submit" value="Submit Order">
    </form>
    '''

# Route to handle the form submission
@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])

    # Insert data into the database
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('INSERT INTO orders (stock_name, quantity) VALUES (?, ?)', (stock_name, quantity))
    conn.commit()
    conn.close()

    # Redirect to stock_view page
    return redirect(url_for('stock_view'))

# Route to view the stocks (for demonstration purposes)
@app.route('/stock_view')
def stock_view():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('SELECT * FROM orders')
    orders = c.fetchall()
    conn.close()

    order_list = '<br>'.join([f'ID: {order[0]}, Stock Name: {order[1]}, Quantity: {order[2]}' for order in orders])
    return f'<h1>Stock Orders</h1>{order_list}'

if __name__ == '__main__':
    init_db()
    app.run(debug=True)