from flask import Flask, request, render_template_string
import sqlite3

app = Flask(__name__)

# HTML template for demonstration purposes
HTML_TEMPLATE = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Buy Stock</title>
  </head>
  <body>
    <h1>Buy Stock</h1>
    <form action="/buy_stock" method="post">
      Quantity: <input type="number" name="quantity" required>
      <button type="submit">Buy</button>
    </form>
  </body>
</html>
'''

def buy_function(quantity):
    # Simulate buying stock logic
    print(f"Bought {quantity} stocks")

@app.route('/')
def index():
    return render_template_string(HTML_TEMPLATE)

@app.route('/buy_stock', methods=['POST'])
def buy_stock():
    quantity = request.form.get('quantity', type=int)
    if quantity is not None:
        # Insert into database (example using SQLite in-memory DB)
        conn = sqlite3.connect(':memory:')
        c = conn.cursor()
        c.execute('''CREATE TABLE IF NOT EXISTS stocks
                     (id INTEGER PRIMARY KEY, quantity INTEGER)''')
        c.execute("INSERT INTO stocks (quantity) VALUES (?)", (quantity,))
        conn.commit()
        conn.close()
        
        # Call buy_function with the quantity
        buy_function(quantity)
    
    return f"Bought {quantity} stocks"

if __name__ == '__main__':
    app.run(debug=True)