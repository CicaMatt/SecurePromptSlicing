from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create an in-memory SQLite database and table for demonstration purposes
def init_db():
    conn = sqlite3.connect(':memory:')
    c = conn.cursor()
    c.execute('''
        CREATE TABLE orders (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user TEXT NOT NULL,
            stock_name TEXT NOT NULL,
            quantity INTEGER NOT NULL
        )
    ''')
    conn.commit()
    return conn

# Initialize the database and create a connection object
conn = init_db()

@app.route('/')
def index():
    form_html = '''
    <form method="post" action="/buy_order">
        User: <input type="text" name="user"><br>
        Stock Name: <input type="text" name="stock_name"><br>
        Quantity: <input type="number" name="quantity"><br>
        <input type="submit" value="Submit">
    </form>
    '''
    return render_template_string(form_html)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    user = request.form.get('user')
    stock_name = request.form.get('stock_name')
    quantity = int(request.form.get('quantity'))

    # Insert the order into the database
    c = conn.cursor()
    c.execute('''
        INSERT INTO orders (user, stock_name, quantity)
        VALUES (?, ?, ?)
    ''', (user, stock_name, quantity))
    conn.commit()

    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    c = conn.cursor()
    c.execute('SELECT * FROM orders')
    orders = c.fetchall()

    view_html = '<h1>Stock Orders</h1>'
    for order in orders:
        view_html += f'<p>User: {order[1]}, Stock Name: {order[2]}, Quantity: {order[3]}</p>'

    return render_template_string(view_html)

if __name__ == '__main__':
    app.run(debug=True)