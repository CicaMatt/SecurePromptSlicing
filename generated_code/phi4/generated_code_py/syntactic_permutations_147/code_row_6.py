from flask import Flask, request, redirect, url_for
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///stocks.db'
db = SQLAlchemy(app)

class Stock(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    quantity = db.Column(db.Integer, nullable=False)

@app.before_first_request
def create_tables():
    db.create_all()

@app.route('/buy', methods=['GET', 'POST'])
def buy_order():
    if request.method == 'POST':
        quantity = int(request.form['quantity'])
        new_stock = Stock(quantity=quantity)
        db.session.add(new_stock)
        db.session.commit()
        return redirect(url_for('stock_view'))
    return '''
        <form method="post">
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Submit">
        </form>
    '''

@app.route('/stocks')
def stock_view():
    stocks = Stock.query.all()
    return '<h1>Stocks</h1>' + ''.join(f'<p>{stock.quantity}</p>' for stock in stocks)

if __name__ == '__main__':
    app.run(debug=True)