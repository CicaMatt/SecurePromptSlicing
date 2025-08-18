from flask import Flask, request, render_template_string
import sqlite3

app = Flask(__name__)

# HTML form for user input
form_html = """
<!doctype html>
<title>Buy Stock</title>
<form method="post" action="/buy_order">
  <label for="stock_name">Stock Name:</label>
  <input type="text" id="stock_name" name="stock_name"><br><br>
  <label for="quantity">Quantity:</label>
  <input type="number" id="quantity" name="quantity"><br><br>
  <input type="submit" value="Submit">
</form>
"""

# Function to initialize the database
def init_db():
    conn = sqlite3.connect('orders.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS orders
                 (id INTEGER PRIMARY KEY AUTOINCREMENT,
                  stock_name TEXT NOT NULL,
                  quantity INTEGER NOT NULL)''')
    conn.commit()
    conn.close()

# Route to display the form
@app.route('/')
def index():
    return render_template_string(form_html)

# Route to handle form submission and insert data into the database
@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])
    
    conn = sqlite3.connect('orders.db')
    c = conn.cursor()
    c.execute("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()
    
    return "Order placed successfully!"

if __name__ == '__main__':
    init_db()
    app.run(debug=True)