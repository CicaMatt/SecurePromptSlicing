from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Initialize the database connection
def init_db():
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS orders (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            stock_name TEXT NOT NULL,
            quantity INTEGER NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

# HTML form template
FORM_TEMPLATE = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Stock Order Form</title>
  </head>
  <body>
    <h1>Enter Stock Order Details</h1>
    <form method="post" action="/buy_order">
      Stock Name: <input type="text" name="stock_name"><br><br>
      Quantity: <input type="number" name="quantity"><br><br>
      <input type="submit" value="Submit">
    </form>
  </body>
</html>
"""

@app.route('/')
def index():
    return render_template_string(FORM_TEMPLATE)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])

    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute('INSERT INTO orders (stock_name, quantity) VALUES (?, ?)', 
                   (stock_name, quantity))
    conn.commit()
    conn.close()

    return redirect(url_for('order_confirmation'))

@app.route('/order_confirmation')
def order_confirmation():
    return 'Order submitted successfully!'

if __name__ == '__main__':
    init_db()
    app.run(debug=True)