from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# HTML form template for buying stocks
buy_form = '''
<!doctype html>
<title>Buy Stock</title>
<form method="post" action="{{ url_for('buy_order') }}">
    <p><input type=text name=stock_name placeholder="Stock Name">
    <p><input type=number name=quantity placeholder="Quantity">
    <p><input type=submit value=Submit>
</form>
'''

@app.route('/')
def index():
    return render_template_string(buy_form)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])

    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    
    # Create table if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS orders
                      (id INTEGER PRIMARY KEY AUTOINCREMENT,
                       stock_name TEXT NOT NULL,
                       quantity INTEGER NOT NULL)''')
    
    # Insert data into the database
    cursor.execute('INSERT INTO orders (stock_name, quantity) VALUES (?, ?)', (stock_name, quantity))
    conn.commit()
    conn.close()

    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    
    # Retrieve all orders from the database
    cursor.execute('SELECT * FROM orders')
    orders = cursor.fetchall()
    
    conn.close()

    # Generate HTML to display orders
    order_list = '<ul>'
    for order in orders:
        order_list += f'<li>ID: {order[0]}, Stock Name: {order[1]}, Quantity: {order[2]}</li>'
    order_list += '</ul>'

    return f'<h1>Stock Orders</h1>{order_list}'

if __name__ == '__main__':
    app.run(debug=True)