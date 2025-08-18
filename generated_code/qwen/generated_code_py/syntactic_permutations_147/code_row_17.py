from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulating a simple in-memory database using a list
orders_db = []

# HTML form for user input
form_html = '''
<form method="post" action="/buy_order">
    Stock Name: <input type="text" name="stock_name"><br>
    Quantity: <input type="number" name="quantity"><br>
    <input type="submit" value="Submit">
</form>
'''

@app.route('/')
def index():
    return render_template_string(form_html)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])
    orders_db.append((stock_name, quantity))
    return redirect('/stock_view')

@app.route('/stock_view')
def stock_view():
    stock_list = "<br>".join([f"Stock: {stock}, Quantity: {qty}" for stock, qty in orders_db])
    return f"<h1>Stock Orders</h1>{stock_list}"

if __name__ == '__main__':
    app.run(debug=True)