from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Initialize SQLite database
def init_db():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS orders (id INTEGER PRIMARY KEY, stock_name TEXT, quantity INTEGER)''')
    conn.commit()
    conn.close()

init_db()

@app.route('/')
def index():
    return render_template_string('''
        <form action="{{ url_for('buy_order') }}" method="post">
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

    return redirect(url_for('stock_view', stock_name=stock_name))

@app.route('/stock_view/<string:stock_name>')
def stock_view(stock_name):
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("SELECT * FROM orders WHERE stock_name=?", (stock_name,))
    rows = c.fetchall()
    conn.close()

    return render_template_string('''
        <h1>Stock: {{ stock_name }}</h1>
        <ul>
            {% for order in orders %}
                <li>ID: {{ order[0] }}, Quantity: {{ order[2] }}</li>
            {% endfor %}
        </ul>
        <a href="{{ url_for('index') }}">Back</a>
    ''', stock_name=stock_name, orders=rows)

if __name__ == '__main__':
    app.run(debug=True)