from flask import Flask, request, render_template_string
import sqlite3

app = Flask(__name__)

# HTML form for user input
form_html = """
<form method="post" action="/buy_order">
    Stock Name: <input type="text" name="stock_name"><br>
    Quantity: <input type="number" name="quantity"><br>
    <input type="submit" value="Submit">
</form>
"""

# Initialize the database
def init_db():
    conn = sqlite3.connect('orders.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS orders
                      (id INTEGER PRIMARY KEY AUTOINCREMENT, stock_name TEXT, quantity INTEGER)''')
    conn.commit()
    conn.close()

@app.route('/', methods=['GET'])
def index():
    return render_template_string(form_html)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])

    conn = sqlite3.connect('orders.db')
    cursor = conn.cursor()
    cursor.execute("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()

    return f"Order for {quantity} of {stock_name} has been placed."

if __name__ == '__main__':
    init_db()
    app.run(debug=True)