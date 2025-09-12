from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Initialize the SQLite database
def init_db():
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS orders (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        stock_name TEXT NOT NULL,
                        quantity INTEGER NOT NULL)''')
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
    cursor = conn.cursor()
    cursor.execute("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()

    return redirect(url_for('stock_view', stock_name=stock_name))

@app.route('/stock_view/<stock_name>')
def stock_view(stock_name):
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM orders WHERE stock_name=?", (stock_name,))
    rows = cursor.fetchall()
    conn.close()

    view_html = f'''
    <h1>Stock Orders for {stock_name}</h1>
    <ul>
    '''
    for row in rows:
        view_html += f'<li>Order ID: {row[0]}, Quantity: {row[2]}</li>'
    
    view_html += '</ul><br><a href="/">Back to Order Form</a>'

    return render_template_string(view_html)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)