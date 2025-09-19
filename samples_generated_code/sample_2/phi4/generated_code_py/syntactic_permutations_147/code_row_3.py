from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Initialize the database
def init_db():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS stock_orders 
                 (id INTEGER PRIMARY KEY AUTOINCREMENT, stock_name TEXT, quantity INTEGER)''')
    conn.commit()
    conn.close()

init_db()

# HTML templates
buy_order_form_template = '''
<!doctype html>
<html lang="en">
  <head><title>Buy Stock</title></head>
  <body>
    <h1>Enter Stock Details to Buy</h1>
    <form method="POST" action="/buy_order">
      Stock Name: <input type="text" name="stock_name"><br>
      Quantity: <input type="number" name="quantity"><br>
      <input type="submit" value="Submit">
    </form>
  </body>
</html>
'''

stock_view_template = '''
<!doctype html>
<html lang="en">
  <head><title>Stock View</title></head>
  <body>
    <h1>Stock Purchase Successful!</h1>
    <p>You have purchased the stock.</p>
  </body>
</html>
'''

@app.route('/')
def index():
    return render_template_string(buy_order_form_template)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])

    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO stock_orders (stock_name, quantity) VALUES (?, ?)", 
              (stock_name, quantity))
    conn.commit()
    conn.close()

    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    return render_template_string(stock_view_template)

if __name__ == '__main__':
    app.run(debug=True)