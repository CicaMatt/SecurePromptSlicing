from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

# Initialize the database
def init_db():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''
        CREATE TABLE IF NOT EXISTS orders (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            stock_name TEXT NOT NULL,
            quantity INTEGER NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

# Route to display the form for entering stock order details
@app.route('/', methods=['GET'])
def index():
    return '''
        <form action="/buy_order" method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Submit Order">
        </form>
    '''

# Route to handle form submission and insert data into the database
@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])

    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('INSERT INTO orders (stock_name, quantity) VALUES (?, ?)', 
              (stock_name, quantity))
    conn.commit()
    conn.close()

    return redirect(url_for('stock_view'))

# Route to view the stock orders
@app.route('/stock_view', methods=['GET'])
def stock_view():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('SELECT * FROM orders')
    rows = c.fetchall()
    
    result = '<h1>Stock Orders</h1>'
    for row in rows:
        result += f'<p>ID: {row[0]}, Stock Name: {row[1]}, Quantity: {row[2]}</p>'
    
    conn.close()
    return result

if __name__ == '__main__':
    init_db()
    app.run(debug=True)