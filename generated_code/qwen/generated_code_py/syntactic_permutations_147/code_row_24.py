from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# In-memory "database" for demonstration purposes
orders_db = []

@app.route('/')
def index():
    return '''
        <form action="/buy_order" method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Submit">
        </form>
    '''

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])
    orders_db.append({'stock_name': stock_name, 'quantity': quantity})
    return redirect('/stock_view')

@app.route('/stock_view')
def stock_view():
    stocks = '<br>'.join([f"Stock: {order['stock_name']}, Quantity: {order['quantity']}" for order in orders_db])
    return f"<h1>Stock Orders</h1>{stocks}"

if __name__ == '__main__':
    app.run(debug=True)