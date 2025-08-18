from flask import Flask, render_template, request, redirect, url_for
import sqlite3

app = Flask(__name__)

# Initialize the SQLite database
conn = sqlite3.connect('orders.db', check_same_thread=False)
cursor = conn.cursor()
cursor.execute('''CREATE TABLE IF NOT EXISTS orders (id INTEGER PRIMARY KEY, symbol TEXT, quantity INTEGER)''')
conn.commit()

@app.route('/')
def stock_view():
    cursor.execute("SELECT * FROM orders")
    orders = cursor.fetchall()
    return render_template('stock_view.html', orders=orders)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    symbol = request.form['symbol']
    quantity = int(request.form['quantity'])
    cursor.execute("INSERT INTO orders (symbol, quantity) VALUES (?, ?)", (symbol, quantity))
    conn.commit()
    return redirect(url_for('stock_view'))

if __name__ == '__main__':
    app.run(debug=True)



<!-- stock_view.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Stock View</title>
</head>
<body>
    <h1>Stock Orders</h1>
    <form action="{{ url_for('buy_order') }}" method="post">
        <label for="symbol">Symbol:</label>
        <input type="text" id="symbol" name="symbol" required><br><br>
        <label for="quantity">Quantity:</label>
        <input type="number" id="quantity" name="quantity" required><br><br>
        <button type="submit">Submit Order</button>
    </form>
    <h2>Current Orders</h2>
    <ul>
        {% for order in orders %}
            <li>{{ order[1] }} - {{ order[2] }}</li>
        {% endfor %}
    </ul>
</body>
</html>