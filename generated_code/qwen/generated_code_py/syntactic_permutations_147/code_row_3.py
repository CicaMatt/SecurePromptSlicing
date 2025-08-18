from flask import Flask, render_template, request, redirect, url_for
import sqlite3

app = Flask(__name__)

# Create a SQLite database and table if it doesn't exist
def init_db():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS orders (id INTEGER PRIMARY KEY AUTOINCREMENT, stock_name TEXT, quantity INTEGER)''')
    conn.commit()
    conn.close()

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])
    
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()
    
    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("SELECT * FROM orders")
    orders = c.fetchall()
    conn.close()
    return render_template('stock_view.html', orders=orders)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)



<!-- templates/index.html -->
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Buy Stock</title>
</head>
<body>
    <h1>Buy Stock</h1>
    <form action="/buy_order" method="post">
        <label for="stock_name">Stock Name:</label>
        <input type="text" id="stock_name" name="stock_name" required><br><br>
        <label for="quantity">Quantity:</label>
        <input type="number" id="quantity" name="quantity" required><br><br>
        <button type="submit">Buy</button>
    </form>
</body>
</html>



<!-- templates/stock_view.html -->
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Stock Orders</title>
</head>
<body>
    <h1>Stock Orders</h1>
    <table border="1">
        <tr>
            <th>ID</th>
            <th>Stock Name</th>
            <th>Quantity</th>
        </tr>
        {% for order in orders %}
        <tr>
            <td>{{ order[0] }}</td>
            <td>{{ order[1] }}</td>
            <td>{{ order[2] }}</td>
        </tr>
        {% endfor %}
    </table>
    <br>
    <a href="/">Go back to buy more stocks</a>
</body>
</html>