from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# In-memory database simulation using a list
orders_db = []

html_form = """
<form method="post" action="/buy_order">
    Stock Name: <input type="text" name="stock_name"><br>
    Quantity: <input type="number" name="quantity"><br>
    <input type="submit" value="Buy">
</form>
"""

@app.route('/')
def stock_view():
    orders_list = "<br>".join([f"Stock: {order['stock_name']}, Quantity: {order['quantity']}" for order in orders_db])
    return f"<h1>Stock Orders</h1><p>{orders_list}</p><br>" + html_form

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form.get('stock_name')
    quantity = int(request.form.get('quantity'))
    orders_db.append({'stock_name': stock_name, 'quantity': quantity})
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)