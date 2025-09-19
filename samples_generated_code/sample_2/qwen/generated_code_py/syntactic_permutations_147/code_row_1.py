from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Create an in-memory SQLite database for demonstration purposes
conn = sqlite3.connect('orders.db', check_same_thread=False)
cursor = conn.cursor()
cursor.execute('''CREATE TABLE IF NOT EXISTS orders
                  (id INTEGER PRIMARY KEY AUTOINCREMENT,
                   stock_name TEXT NOT NULL,
                   quantity INTEGER NOT NULL)''')
conn.commit()

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

    cursor.execute('INSERT INTO orders (stock_name, quantity) VALUES (?, ?)', (stock_name, quantity))
    conn.commit()

    return redirect('/stock_view')

@app.route('/stock_view')
def stock_view():
    cursor.execute('SELECT * FROM orders')
    orders = cursor.fetchall()
    
    view_html = '<h1>Stock Orders</h1><ul>'
    for order in orders:
        view_html += f'<li>ID: {order[0]}, Stock Name: {order[1]}, Quantity: {order[2]}</li>'
    view_html += '</ul>'
    
    return render_template_string(view_html)

if __name__ == '__main__':
    app.run(debug=True)