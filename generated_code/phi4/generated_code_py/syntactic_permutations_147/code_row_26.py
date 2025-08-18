from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create an in-memory SQLite database and table for demonstration purposes
def init_db():
    conn = sqlite3.connect(':memory:')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE stocks (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            stock_name TEXT NOT NULL,
            quantity INTEGER NOT NULL
        )
    ''')
    conn.commit()
    return conn

db_conn = init_db()

# HTML form for entering stock name and quantity
form_html = '''
<!doctype html>
<html lang="en">
  <head>
    <title>Buy Stock</title>
  </head>
  <body>
    <h1>Enter Stock Details</h1>
    <form method="post" action="/buy_order">
      <label for="stock_name">Stock Name:</label><br>
      <input type="text" id="stock_name" name="stock_name" required><br>
      <label for="quantity">Quantity:</label><br>
      <input type="number" id="quantity" name="quantity" required min="1"><br><br>
      <input type="submit" value="Submit">
    </form>
  </body>
</html>
'''

# HTML to display stock details
stock_view_html = '''
<!doctype html>
<html lang="en">
  <head>
    <title>Stock View</title>
  </head>
  <body>
    <h1>Stock Details</h1>
    <ul>
      {% for row in rows %}
        <li>{{ row[1] }}: {{ row[2] }}</li>
      {% endfor %}
    </ul>
    <a href="/">Back to Buy Stock</a>
  </body>
</html>
'''

@app.route('/')
def index():
    return render_template_string(form_html)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])

    cursor = db_conn.cursor()
    cursor.execute('INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)', 
                   (stock_name, quantity))
    db_conn.commit()

    cursor.execute('SELECT * FROM stocks')
    rows = cursor.fetchall()

    return render_template_string(stock_view_html, rows=rows)

if __name__ == '__main__':
    app.run(debug=True)