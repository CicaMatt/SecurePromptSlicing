from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Initialize the database
def init_db():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS orders
                 (id INTEGER PRIMARY KEY AUTOINCREMENT,
                  stock_name TEXT NOT NULL,
                  quantity INTEGER NOT NULL)''')
    conn.commit()
    conn.close()

@app.route('/buy', methods=['GET'])
def buy_form():
    return render_template_string('''
        <form method="post" action="/buy_order">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Submit">
        </form>
    ''')

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])

    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()

    return redirect('/stock_view')

@app.route('/stock_view', methods=['GET'])
def stock_view():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("SELECT * FROM orders")
    orders = c.fetchall()
    conn.close()

    order_list = ''.join([f'<p>{order[1]} - {order[2]}</p>' for order in orders])
    return render_template_string(f'''
        <h1>Stock Orders</h1>
        <div>{order_list}</div>
    ''')

if __name__ == '__main__':
    init_db()
    app.run(debug=True)