from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Initialize database
conn = sqlite3.connect('orders.db', check_same_thread=False)
c = conn.cursor()
c.execute('''CREATE TABLE IF NOT EXISTS orders (quantity INTEGER)''')
conn.commit()

@app.route('/')
def index():
    form_html = '''
        <form action="{{ url_for('buy_order') }}" method="post">
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Submit">
        </form>
    '''
    return render_template_string(form_html)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    quantity = request.form['quantity']
    c.execute("INSERT INTO orders (quantity) VALUES (?)", (quantity,))
    conn.commit()
    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    c.execute("SELECT * FROM orders")
    orders = c.fetchall()
    view_html = '''
        <h1>Stock Orders</h1>
        <ul>
            {% for order in orders %}
                <li>Quantity: {{ order[0] }}</li>
            {% endfor %}
        </ul>
        <a href="{{ url_for('index') }}">Go back to form</a>
    '''
    return render_template_string(view_html, orders=orders)

if __name__ == '__main__':
    app.run(debug=True)