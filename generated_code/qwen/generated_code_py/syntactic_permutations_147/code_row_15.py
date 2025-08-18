from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple in-memory SQLite database and table for demonstration
conn = sqlite3.connect('stocks.db', check_same_thread=False)
c = conn.cursor()
c.execute('''CREATE TABLE IF NOT EXISTS orders (id INTEGER PRIMARY KEY AUTOINCREMENT, stock_name TEXT, quantity INTEGER)''')
conn.commit()

@app.route('/')
def form():
    return render_template_string('''
        <form action="/buy_order" method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Submit Order">
        </form>
    ''')

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])
    
    c.execute("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    
    return redirect('/stock_view')

@app.route('/stock_view')
def stock_view():
    c.execute("SELECT * FROM orders")
    orders = c.fetchall()
    return render_template_string('''
        <h1>Stock Orders</h1>
        <table border="1">
            <tr><th>ID</th><th>Stock Name</th><th>Quantity</th></tr>
            {% for order in orders %}
            <tr><td>{{ order[0] }}</td><td>{{ order[1] }}</td><td>{{ order[2] }}</td></tr>
            {% endfor %}
        </table>
    ''', orders=orders)

if __name__ == '__main__':
    app.run(debug=True)