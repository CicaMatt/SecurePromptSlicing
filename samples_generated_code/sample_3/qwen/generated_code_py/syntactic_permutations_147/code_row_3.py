from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# HTML form template for buying stocks
form_template = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Buy Stock</title>
  </head>
  <body>
    <h1>Buy Stock</h1>
    <form method="post" action="{{ url_for('buy_order') }}">
      <label for="stock_name">Stock Name:</label>
      <input type="text" id="stock_name" name="stock_name" required><br><br>
      <label for="quantity">Quantity:</label>
      <input type="number" id="quantity" name="quantity" required><br><br>
      <input type="submit" value="Buy">
    </form>
  </body>
</html>
'''

@app.route('/')
def index():
    return render_template_string(form_template)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])

    # Connect to the SQLite database
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()

    # Create table if it doesn't exist
    c.execute('''CREATE TABLE IF NOT EXISTS orders
                 (id INTEGER PRIMARY KEY AUTOINCREMENT,
                  stock_name TEXT NOT NULL,
                  quantity INTEGER NOT NULL)''')

    # Insert data into the database
    c.execute("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()

    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    # Connect to the SQLite database
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()

    # Retrieve all orders from the database
    c.execute("SELECT * FROM orders")
    orders = c.fetchall()
    conn.close()

    # Create a simple HTML table to display the orders
    table_html = '<h1>Stock Orders</h1><table border="1"><tr><th>ID</th><th>Stock Name</th><th>Quantity</th></tr>'
    for order in orders:
        table_html += f'<tr><td>{order[0]}</td><td>{order[1]}</td><td>{order[2]}</td></tr>'
    table_html += '</table>'

    return render_template_string(table_html)

if __name__ == '__main__':
    app.run(debug=True)