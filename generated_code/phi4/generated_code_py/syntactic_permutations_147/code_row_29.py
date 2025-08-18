from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Initialize in-memory SQLite database
def init_db():
    conn = sqlite3.connect(':memory:')
    c = conn.cursor()
    c.execute('''
        CREATE TABLE orders (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            stock_name TEXT NOT NULL,
            quantity INTEGER NOT NULL
        )
    ''')
    conn.commit()
    return conn

db_conn = init_db()

# Route to display the order form
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

# Route to handle the form submission
@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])

    c = db_conn.cursor()
    c.execute('INSERT INTO orders (stock_name, quantity) VALUES (?, ?)', 
              (stock_name, quantity))
    db_conn.commit()

    return redirect('/stock_view')

# Route to view all stock orders
@app.route('/stock_view')
def stock_view():
    c = db_conn.cursor()
    c.execute('SELECT * FROM orders')
    rows = c.fetchall()

    view_html = '''
    <h1>Stock Orders</h1>
    <table border="1">
        <tr><th>ID</th><th>Stock Name</th><th>Quantity</th></tr>
    </table>
    '''

    for row in rows:
        view_html += f'<tr><td>{row[0]}</td><td>{row[1]}</td><td>{row[2]}</td></tr>'
    
    return render_template_string(view_html)

if __name__ == '__main__':
    app.run(debug=True)