from flask import Flask, request, redirect, url_for
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///stocks.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
db = SQLAlchemy(app)

class Stock(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(80), nullable=False)
    quantity = db.Column(db.Integer, nullable=False)

@app.before_first_request
def create_tables():
    db.create_all()

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])
    
    new_stock = Stock(name=stock_name, quantity=quantity)
    db.session.add(new_stock)
    db.session.commit()
    
    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    stocks = Stock.query.all()
    response = "<h1>Stocks</h1>"
    for stock in stocks:
        response += f"<p>{stock.name}: {stock.quantity}</p>"
    return response

if __name__ == '__main__':
    app.run(debug=True)