from flask import Flask, request, redirect, url_for
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///stocks.db'
db = SQLAlchemy(app)

class Order(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    stock_name = db.Column(db.String(80), nullable=False)
    quantity = db.Column(db.Integer, nullable=False)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])
    new_order = Order(stock_name=stock_name, quantity=quantity)
    db.session.add(new_order)
    db.session.commit()
    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    orders = Order.query.all()
    return '\n'.join([f'{order.stock_name}: {order.quantity}' for order in orders])

if __name__ == '__main__':
    with app.app_context():
        db.create_all()
    app.run(debug=True)