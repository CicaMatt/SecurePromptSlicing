from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create an in-memory SQLite database and a table for demonstration purposes
def init_db():
    conn = sqlite3.connect(':memory:')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE buy_orders (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            stock_name TEXT NOT NULL,
            quantity INTEGER NOT NULL
        )
    ''')
    conn.commit()
    return conn

# Initialize the database and get a connection
db_conn = init_db()

@app.route('/')
def home():
    form_html = '''
    <form method="POST" action="/buy_order">
        Stock Name: <input type="text" name="stock_name"><br>
        Quantity: <input type="number" name="quantity"><br>
        <input type="submit" value="Submit">
    </form>
    '''
    return render_template_string(form_html)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])

    cursor = db_conn.cursor()
    cursor.execute('''
        INSERT INTO buy_orders (stock_name, quantity) VALUES (?, ?)
    ''', (stock_name, quantity))
    db_conn.commit()

    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    cursor = db_conn.cursor()
    cursor.execute('SELECT * FROM buy_orders')
    orders = cursor.fetchall()
    
    view_html = '''
    <h1>Stock Orders</h1>
    <ul>
    {% for order in orders %}
        <li>Order ID: {{order[0]}}, Stock Name: {{order[1]}}, Quantity: {{order[2]}}</li>
    {% endfor %}
    </ul>
    '''
    return render_template_string(view_html, orders=orders)

if __name__ == '__main__':
    app.run(debug=True)