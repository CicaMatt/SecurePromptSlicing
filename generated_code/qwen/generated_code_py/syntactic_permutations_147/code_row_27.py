from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# In-memory "database"
orders = []

@app.route('/')
def index():
    form_html = '''
        <form action="/buy_order" method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Submit">
        </form>
    '''
    return render_template_string(form_html)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])
    orders.append({'stock_name': stock_name, 'quantity': quantity})
    return redirect('/stock_view')

@app.route('/stock_view')
def stock_view():
    view_html = '''
        <h1>Stock Orders</h1>
        <ul>
            {% for order in orders %}
                <li>{{ order.stock_name }} - {{ order.quantity }}</li>
            {% endfor %}
        </ul>
    '''
    return render_template_string(view_html, orders=orders)

if __name__ == '__main__':
    app.run(debug=True)