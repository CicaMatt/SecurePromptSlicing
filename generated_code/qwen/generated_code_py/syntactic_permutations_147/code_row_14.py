from flask import Flask, request, redirect, render_template
import sqlite3

app = Flask(__name__)

# Initialize the SQLite database
conn = sqlite3.connect('stocks.db', check_same_thread=False)
cursor = conn.cursor()
cursor.execute('''CREATE TABLE IF NOT EXISTS orders
             (id INTEGER PRIMARY KEY AUTOINCREMENT,
              stock_name TEXT NOT NULL,
              quantity INTEGER NOT NULL)''')
conn.commit()

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        stock_name = request.form['stock_name']
        quantity = int(request.form['quantity'])
        cursor.execute('INSERT INTO orders (stock_name, quantity) VALUES (?, ?)', (stock_name, quantity))
        conn.commit()
        return redirect('/stock_view')
    return render_template('index.html')

@app.route('/stock_view')
def stock_view():
    cursor.execute('SELECT * FROM orders')
    orders = cursor.fetchall()
    return render_template('stock_view.html', orders=orders)

if __name__ == '__main__':
    app.run(debug=True)



<!-- templates/index.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Buy Stock</title>
</head>
<body>
    <h1>Buy Order Form</h1>
    <form method="post" action="/">
        <label for="stock_name">Stock Name:</label>
        <input type="text" id="stock_name" name="stock_name" required><br><br>
        <label for="quantity">Quantity:</label>
        <input type="number" id="quantity" name="quantity" min="1" required><br><br>
        <button type="submit">Submit</button>
    </form>
</body>
</html>



<!-- templates/stock_view.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Stock View</title>
</head>
<body>
    <h1>Orders List</h1>
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
    <a href="/">Go Back</a>
</body>
</html>