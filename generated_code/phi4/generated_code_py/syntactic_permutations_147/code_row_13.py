from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple in-memory SQLite database and table
def init_db():
    conn = sqlite3.connect(':memory:')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE orders (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            symbol TEXT NOT NULL,
            quantity INTEGER NOT NULL
        )
    ''')
    conn.commit()
    return conn

# Initialize the database connection
conn = init_db()

@app.route('/')
def index():
    form_html = '''
    <form method="post" action="/buy_order">
        Symbol: <input type="text" name="symbol"><br>
        Quantity: <input type="number" name="quantity"><br>
        <input type="submit" value="Buy Order">
    </form>
    '''
    return render_template_string(form_html)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    symbol = request.form['symbol']
    quantity = int(request.form['quantity'])

    cursor = conn.cursor()
    cursor.execute('INSERT INTO orders (symbol, quantity) VALUES (?, ?)', (symbol, quantity))
    conn.commit()

    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    cursor = conn.cursor()
    cursor.execute('SELECT * FROM orders')
    rows = cursor.fetchall()

    view_html = '''
    <h1>Stock Orders</h1>
    <ul>
        {% for row in rows %}
            <li>ID: {{row[0]}}, Symbol: {{row[1]}}, Quantity: {{row[2]}}</li>
        {% endfor %}
    </ul>
    <a href="/">Back to Form</a>
    '''
    return render_template_string(view_html, rows=rows)

if __name__ == '__main__':
    app.run(debug=True)