from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

# Create a database connection
def get_db_connection():
    conn = sqlite3.connect('stocks.db')
    conn.row_factory = sqlite3.Row
    return conn

# Initialize the database
def init_db():
    conn = get_db_connection()
    with open('schema.sql') as f:
        conn.executescript(f.read())
    conn.close()

@app.route('/')
def index():
    return '''
        <form method="post" action="/buy_order">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Buy Order">
        </form>
    '''

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])

    conn = get_db_connection()
    conn.execute('INSERT INTO orders (stock_name, quantity) VALUES (?, ?)',
                 (stock_name, quantity))
    conn.commit()
    conn.close()

    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    conn = get_db_connection()
    stocks = conn.execute('SELECT * FROM orders').fetchall()
    conn.close()

    stocks_list = '<br>'.join([f'Stock Name: {row["stock_name"]}, Quantity: {row["quantity"]}' for row in stocks])
    
    return f'<h1>Stock Orders</h1><p>{stocks_list}</p>'

if __name__ == '__main__':
    with open('schema.sql', 'w') as f:
        f.write('''
            CREATE TABLE IF NOT EXISTS orders (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                stock_name TEXT NOT NULL,
                quantity INTEGER NOT NULL
            );
        ''')

    init_db()
    app.run(debug=True)