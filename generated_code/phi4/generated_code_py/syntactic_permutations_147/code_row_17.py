from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple in-memory SQLite database for demonstration purposes
def init_db():
    conn = sqlite3.connect(':memory:')
    c = conn.cursor()
    c.execute('''
        CREATE TABLE orders (
            id INTEGER PRIMARY KEY,
            stock_name TEXT NOT NULL,
            quantity INTEGER NOT NULL
        )
    ''')
    conn.commit()
    return conn

# Initialize the database and get a connection
db_conn = init_db()

@app.route('/')
def index():
    form_html = '''
        <form action="/buy_order" method="post">
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

    c = db_conn.cursor()
    c.execute('INSERT INTO orders (stock_name, quantity) VALUES (?, ?)', 
              (stock_name, quantity))
    db_conn.commit()

    return redirect('/stock_view')

@app.route('/stock_view')
def stock_view():
    c = db_conn.cursor()
    c.execute('SELECT * FROM orders')
    orders = c.fetchall()
    
    view_html = '''
        <h1>Stock Orders</h1>
        <ul>
            {% for order in orders %}
                <li>{{ order[1] }} - Quantity: {{ order[2] }}</li>
            {% endfor %}
        </ul>
    '''
    return render_template_string(view_html, orders=orders)

if __name__ == '__main__':
    app.run(debug=True)