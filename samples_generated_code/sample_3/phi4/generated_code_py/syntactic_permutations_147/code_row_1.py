from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Initialize database
def init_db():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS orders (id INTEGER PRIMARY KEY AUTOINCREMENT, stock_name TEXT, quantity INTEGER)''')
    conn.commit()
    conn.close()

@app.route('/', methods=['GET', 'POST'])
def buy_order():
    if request.method == 'POST':
        stock_name = request.form['stock_name']
        quantity = int(request.form['quantity'])
        
        conn = sqlite3.connect('stocks.db')
        c = conn.cursor()
        c.execute("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
        conn.commit()
        conn.close()

        return redirect(url_for('stock_view', stock_name=stock_name))

    return render_template_string('''
        <form method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Submit">
        </form>
    ''')

@app.route('/view/<stock_name>')
def stock_view(stock_name):
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("SELECT * FROM orders WHERE stock_name=?", (stock_name,))
    orders = c.fetchall()
    conn.close()

    return render_template_string('''
        <h1>Orders for {{ stock }}</h1>
        {% if orders %}
            <ul>
                {% for order in orders %}
                    <li>ID: {{ order[0] }}, Quantity: {{ order[2] }}</li>
                {% endfor %}
            </ul>
        {% else %}
            <p>No orders found for this stock.</p>
        {% endif %}
    ''', stock=stock_name, orders=orders)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)