from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# In-memory "database" for demonstration purposes
database = []

@app.route('/', methods=['GET', 'POST'])
def buy_order():
    if request.method == 'POST':
        stock_name = request.form['stock_name']
        quantity = int(request.form['quantity'])
        database.append({'stock_name': stock_name, 'quantity': quantity})
        return redirect('/stock_view')
    return render_template_string('''
        <form method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Submit">
        </form>
    ''')

@app.route('/stock_view')
def stock_view():
    return render_template_string('''
        <h1>Stock Orders</h1>
        <ul>
            {% for order in database %}
                <li>{{ order.stock_name }} - {{ order.quantity }}</li>
            {% endfor %}
        </ul>
    ''', database=database)

if __name__ == '__main__':
    app.run(debug=True)