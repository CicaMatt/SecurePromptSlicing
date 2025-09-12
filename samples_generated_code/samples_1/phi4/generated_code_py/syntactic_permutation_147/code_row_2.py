from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Initialize SQLite Database
def init_db():
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS orders (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            stock_name TEXT NOT NULL,
            quantity INTEGER NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

@app.route('/buy_order', methods=['GET', 'POST'])
def buy_order():
    if request.method == 'POST':
        stock_name = request.form['stock_name']
        quantity = int(request.form['quantity'])

        # Insert into database
        conn = sqlite3.connect('stocks.db')
        cursor = conn.cursor()
        cursor.execute('INSERT INTO orders (stock_name, quantity) VALUES (?, ?)', 
                       (stock_name, quantity))
        conn.commit()
        conn.close()

        return redirect('/stock_view')

    return render_template_string('''
        <form method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Submit">
        </form>
    ''')

@app.route('/stock_view')
def stock_view():
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute('SELECT * FROM orders')
    orders = cursor.fetchall()
    conn.close()

    return render_template_string('''
        <h1>Stock Orders</h1>
        <ul>
            {% for order in orders %}
                <li>{{ loop.index }}: {{ order[1] }} - Quantity: {{ order[2] }}</li>
            {% endfor %}
        </ul>
    ''', orders=orders)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)