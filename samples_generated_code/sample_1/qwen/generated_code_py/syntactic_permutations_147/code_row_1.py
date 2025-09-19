from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# In-memory "database" for demonstration purposes
orders_db = []

html_form = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Buy Stock</title>
  </head>
  <body>
    <h1>Buy Stock</h1>
    <form action="/buy_order" method="post">
      <label for="stock_name">Stock Name:</label>
      <input type="text" id="stock_name" name="stock_name"><br><br>
      <label for="quantity">Quantity:</label>
      <input type="number" id="quantity" name="quantity"><br><br>
      <input type="submit" value="Submit">
    </form>
  </body>
</html>
"""

@app.route('/')
def index():
    return render_template_string(html_form)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])
    orders_db.append({'stock_name': stock_name, 'quantity': quantity})
    return redirect('/stock_view')

@app.route('/stock_view')
def stock_view():
    stocks_html = "<h1>Stock Orders</h1><ul>"
    for order in orders_db:
        stocks_html += f"<li>{order['stock_name']}: {order['quantity']}</li>"
    stocks_html += "</ul>"
    return render_template_string(stocks_html)

if __name__ == '__main__':
    app.run(debug=True)