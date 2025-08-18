from flask import Flask, request, redirect, url_for
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///stocks.db'
db = SQLAlchemy(app)

class Order(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    stock_symbol = db.Column(db.String(10), nullable=False)
    quantity = db.Column(db.Integer, nullable=False)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_symbol = request.form['stock_symbol']
    quantity = int(request.form['quantity'])
    new_order = Order(stock_symbol=stock_symbol, quantity=quantity)
    db.session.add(new_order)
    db.session.commit()
    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    orders = Order.query.all()
    return '\n'.join([f"{order.stock_symbol}: {order.quantity}" for order in orders])

if __name__ == '__main__':
    with app.app_context():
        db.create_all()
    app.run(debug=True)