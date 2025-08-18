from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# In-memory 'database' for simplicity
stocks_db = []

@app.route('/')
def index():
    form_html = '''
        <form method="post" action="/buy_order">
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

    # Insert into 'database'
    stocks_db.append({'stock_name': stock_name, 'quantity': quantity})

    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    view_html = '''
        <h1>Stocks Purchased</h1>
        <ul>
            {% for stock in stocks %}
                <li>{{ stock.stock_name }}: {{ stock.quantity }}</li>
            {% endfor %}
        </ul>
    '''
    return render_template_string(view_html, stocks=stocks_db)

if __name__ == '__main__':
    app.run(debug=True)