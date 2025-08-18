from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Database setup
def init_db():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS buy_orders 
                 (id INTEGER PRIMARY KEY, stock_name TEXT, quantity INTEGER)''')
    conn.commit()
    conn.close()

@app.route('/')
def index():
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

    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO buy_orders (stock_name, quantity) VALUES (?, ?)", 
              (stock_name, quantity))
    conn.commit()
    conn.close()

    return redirect('/stock_view')

@app.route('/stock_view')
def stock_view():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("SELECT * FROM buy_orders")
    orders = c.fetchall()
    conn.close()

    view_html = '''
    <h1>Stock Orders</h1>
    <ul>
        {% for order in orders %}
            <li>{{ order[1] }} - {{ order[2] }}</li>
        {% endfor %}
    </ul>
    <a href="/">Back to Order Form</a>
    '''
    return render_template_string(view_html, orders=orders)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)