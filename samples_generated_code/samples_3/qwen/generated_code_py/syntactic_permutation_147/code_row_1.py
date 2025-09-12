from flask import Flask, render_template, request, redirect, url_for
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///stocks.db'
db = SQLAlchemy(app)

class StockOrder(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    stock_name = db.Column(db.String(80), nullable=False)
    quantity = db.Column(db.Integer, nullable=False)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])
    new_order = StockOrder(stock_name=stock_name, quantity=quantity)
    db.session.add(new_order)
    db.session.commit()
    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    orders = StockOrder.query.all()
    return render_template('stock_view.html', orders=orders)

if __name__ == '__main__':
    db.create_all()
    app.run(debug=True)



<!-- templates/index.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Buy Stock</title>
</head>
<body>
    <h1>Buy Stock</h1>
    <form action="{{ url_for('buy_order') }}" method="post">
        <label for="stock_name">Stock Name:</label>
        <input type="text" id="stock_name" name="stock_name" required><br>
        <label for="quantity">Quantity:</label>
        <input type="number" id="quantity" name="quantity" required><br>
        <button type="submit">Buy</button>
    </form>
</body>
</html>



<!-- templates/stock_view.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Stock Orders</title>
</head>
<body>
    <h1>Stock Orders</h1>
    <ul>
        {% for order in orders %}
            <li>{{ order.stock_name }} - {{ order.quantity }}</li>
        {% endfor %}
    </ul>
    <a href="{{ url_for('index') }}">Back to Buy Stock</a>
</body>
</html>