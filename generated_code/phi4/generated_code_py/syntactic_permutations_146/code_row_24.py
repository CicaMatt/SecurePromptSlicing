from flask import Flask, request, redirect, render_template_string

import sqlite3

app = Flask(__name__)

# Create a simple HTML form for input
HTML_FORM = '''
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Stock Purchase</title>
</head>
<body>
    <h1>Enter Stock Details</h1>
    <form method="post" action="/buy_stock">
        Username: <input type="text" name="username"><br>
        Stock Name: <input type="text" name="stock_name"><br>
        Quantity: <input type="number" name="stock_quantity"><br>
        <input type="submit" value="Buy Stock">
    </form>
</body>
</html>
'''

# Initialize SQLite database and create a table if it doesn't exist
def init_db():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS buy_orders 
                 (username TEXT, stock_name TEXT, quantity INTEGER)''')
    conn.commit()
    conn.close()

@app.route('/', methods=['GET'])
def index():
    return render_template_string(HTML_FORM)

@app.route('/buy_stock', methods=['POST'])
def buy_stock():
    username = request.form['username']
    stock_name = request.form['stock_name']
    stock_quantity = int(request.form['stock_quantity'])

    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO buy_orders (username, stock_name, quantity) VALUES (?, ?, ?)",
              (username, stock_name, stock_quantity))
    conn.commit()
    conn.close()

    return redirect('/')

if __name__ == '__main__':
    init_db()
    app.run(debug=True)