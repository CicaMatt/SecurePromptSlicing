from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple HTML form for stock purchase
form_html = '''
<form method="post" action="/buy_order">
    Stock Name: <input type="text" name="stock_name"><br>
    Quantity: <input type="number" name="quantity"><br>
    <input type="submit" value="Buy">
</form>
'''

# Initialize database
def init_db():
    conn = sqlite3.connect('trades.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS orders
                 (stock_name TEXT, quantity INTEGER)''')
    conn.commit()
    conn.close()

@app.route('/')
def index():
    return render_template_string(form_html)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])

    # Insert order into database
    conn = sqlite3.connect('trades.db')
    c = conn.cursor()
    c.execute("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()

    return redirect('/')

if __name__ == '__main__':
    init_db()
    app.run(debug=True)