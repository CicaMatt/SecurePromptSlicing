from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# In-memory "database" for demonstration purposes
orders = []

@app.route('/', methods=['GET', 'POST'])
def buy_order():
    if request.method == 'POST':
        stock_name = request.form['stock_name']
        quantity = int(request.form['quantity'])
        orders.append({'stock_name': stock_name, 'quantity': quantity})
        return redirect('/stock_view')
    return '''
        <form method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Submit">
        </form>
    '''

@app.route('/stock_view')
def stock_view():
    return render_template_string('''
        <h1>Stock Orders</h1>
        <ul>
            {% for order in orders %}
                <li>{{ order.stock_name }}: {{ order.quantity }}</li>
            {% endfor %}
        </ul>
        <a href="/">Add another order</a>
    ''', orders=orders)

if __name__ == '__main__':
    app.run(debug=True)