from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create a sample database and table for demonstration purposes
def init_db():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS orders (
                 id INTEGER PRIMARY KEY AUTOINCREMENT,
                 stock_name TEXT NOT NULL,
                 quantity INTEGER NOT NULL)''')
    conn.commit()
    conn.close()

init_db()

# HTML templates
buy_form_html = '''
<!doctype html>
<title>Buy Stock</title>
<h1>Enter Stock Details</h1>
<form method=post action="/buy_order">
  <label for="stock_name">Stock Name:</label><br>
  <input type="text" id="stock_name" name="stock_name" required><br>
  <label for="quantity">Quantity:</label><br>
  <input type="number" id="quantity" name="quantity" required><br><br>
  <input type="submit" value="Submit">
</form>
'''

stock_view_html = '''
<!doctype html>
<title>Stock View</title>
<h1>Order Placed Successfully!</h1>
<p>Thank you for placing your order.</p>
<a href="/">Back to Order Page</a>
'''

@app.route('/', methods=['GET'])
def buy_stock():
    return render_template_string(buy_form_html)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])
    
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()

    return redirect(url_for('stock_view'))

@app.route('/stock_view', methods=['GET'])
def stock_view():
    return render_template_string(stock_view_html)

if __name__ == '__main__':
    app.run(debug=True)