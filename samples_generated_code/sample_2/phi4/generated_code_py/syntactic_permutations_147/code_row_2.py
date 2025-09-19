from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Initialize the database
def init_db():
    with sqlite3.connect('stocks.db') as conn:
        cursor = conn.cursor()
        cursor.execute('''CREATE TABLE IF NOT EXISTS orders (
                            id INTEGER PRIMARY KEY AUTOINCREMENT,
                            stock_name TEXT NOT NULL,
                            quantity INTEGER NOT NULL)''')
        conn.commit()

@app.route('/')
def index():
    form_html = '''
    <form action="/buy_order" method="post">
        Stock Name: <input type="text" name="stock_name"><br>
        Quantity: <input type="number" name="quantity"><br>
        <input type="submit" value="Submit Order">
    </form>
    '''
    return render_template_string(form_html)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])

    with sqlite3.connect('stocks.db') as conn:
        cursor = conn.cursor()
        cursor.execute("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
        conn.commit()

    return redirect('/stock_view')

@app.route('/stock_view')
def stock_view():
    with sqlite3.connect('stocks.db') as conn:
        cursor = conn.cursor()
        cursor.execute("SELECT * FROM orders")
        orders = cursor.fetchall()
        
    view_html = '''
    <h1>Stock Orders</h1>
    <ul>
    {% for order in orders %}
        <li>{{ order[1] }}: {{ order[2] }}</li>
    {% endfor %}
    </ul>
    <a href="/">Back to Order Form</a>
    '''
    return render_template_string(view_html, orders=orders)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)