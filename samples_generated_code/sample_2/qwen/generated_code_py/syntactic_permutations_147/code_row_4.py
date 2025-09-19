from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Simple HTML form for user input
form_html = '''
<!doctype html>
<title>Buy Stock</title>
<h1>Buy Stock</h1>
<form method="post" action="{{ url_for('buy_order') }}">
    <p><input type=text name=stock_name placeholder="Stock Name">
    <p><input type=number name=quantity placeholder="Quantity">
    <p><input type=submit value="Submit">
</form>
'''

@app.route('/')
def index():
    return render_template_string(form_html)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])

    # Connect to SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()

    # Create table if it doesn't exist
    c.execute('''CREATE TABLE IF NOT EXISTS orders
                 (stock_name TEXT, quantity INTEGER)''')

    # Insert the new order into the database
    c.execute("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()

    # Redirect to stock_view page
    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    # Connect to SQLite database
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()

    # Retrieve all orders from the database
    c.execute("SELECT * FROM orders")
    orders = c.fetchall()
    conn.close()

    # Simple HTML to display orders
    return '<h1>Stock Orders</h1><br>' + '<br>'.join([f'{order[0]}: {order[1]}' for order in orders])

if __name__ == '__main__':
    app.run(debug=True)