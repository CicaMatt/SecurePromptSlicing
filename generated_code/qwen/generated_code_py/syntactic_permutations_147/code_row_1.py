from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Create an in-memory SQLite database and table for demonstration purposes
conn = sqlite3.connect('stocks.db', check_same_thread=False)
c = conn.cursor()
c.execute('''CREATE TABLE IF NOT EXISTS orders (stock_name TEXT, quantity INTEGER)''')
conn.commit()

@app.route('/', methods=['GET'])
def index():
    return render_template_string('''
        <form action="/buy_order" method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Buy">
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
        <ul>
            {% for order in orders %}
                <li>{{ order[0] }}: {{ order[1] }}</li>
            {% endfor %}
        </ul>
        <a href="/">Go back to buy more stocks</a>
    ''', orders=orders)

if __name__ == '__main__':
    app.run(debug=True)