from flask import Flask, request, render_template_string
import sqlite3

app = Flask(__name__)

# Initialize the database
def init_db():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS buy_orders (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    stock_name TEXT NOT NULL,
                    quantity INTEGER NOT NULL)''')
    conn.commit()
    conn.close()

init_db()

# HTML template for the form
HTML_TEMPLATE = '''
<!doctype html>
<html>
<head><title>Buy Stock</title></head>
<body>
  <h2>Enter Stock Information</h2>
  <form method="post" action="/buy_order">
    Stock Name: <input type="text" name="stock_name"><br>
    Quantity: <input type="number" name="quantity"><br><br>
    <input type="submit" value="Submit">
  </form>
</body>
</html>
'''

@app.route('/', methods=['GET'])
def index():
    return render_template_string(HTML_TEMPLATE)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])

    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO buy_orders (stock_name, quantity) VALUES (?, ?)", 
              (stock_name, quantity))
    conn.commit()
    conn.close()

    return f"Order for {quantity} shares of {stock_name} has been placed."

if __name__ == '__main__':
    app.run(debug=True)