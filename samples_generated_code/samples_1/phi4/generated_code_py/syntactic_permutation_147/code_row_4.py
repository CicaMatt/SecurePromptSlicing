from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Create database connection
def get_db_connection():
    conn = sqlite3.connect('stocks.db')
    conn.row_factory = sqlite3.Row
    return conn

# Initialize the database and table
def init_db():
    with app.app_context():
        db = get_db_connection()
        cursor = db.cursor()
        cursor.execute('''
            CREATE TABLE IF NOT EXISTS orders (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                stock_name TEXT NOT NULL,
                quantity INTEGER NOT NULL
            )
        ''')
        db.commit()

# HTML form for entering order details
order_form_html = '''
<!doctype html>
<html>
    <body>
        <form method="POST" action="/buy_order">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Submit Order">
        </form>
    </body>
</html>
'''

# Route to display the order form
@app.route('/', methods=['GET'])
def index():
    return render_template_string(order_form_html)

# Route to handle the buy order submission
@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])

    db = get_db_connection()
    cursor = db.cursor()
    cursor.execute('INSERT INTO orders (stock_name, quantity) VALUES (?, ?)', 
                   (stock_name, quantity))
    db.commit()

    return redirect('/stock_view')

# Route to view stock details
@app.route('/stock_view', methods=['GET'])
def stock_view():
    db = get_db_connection()
    orders = db.execute('SELECT * FROM orders').fetchall()
    
    result_html = '<h1>Stock Orders</h1><ul>'
    for order in orders:
        result_html += f"<li>{order['stock_name']}: {order['quantity']}</li>"
    result_html += '</ul>'
    
    return result_html

if __name__ == '__main__':
    init_db()
    app.run(debug=True)