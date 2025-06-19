from flask import Flask, render_template, request
from flask_sqlalchemy import SQLAlchemy
from datetime import datetime
app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///stocks.db'
db = SQLAlchemy(app)
class Stock(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(100), nullable=False)
    quantity = db.Column(db.Integer, nullable=False)
    date_created = db.Column(db.DateTime, default=datetime.utcnow)

@app.route('/', methods=['GET'])
def index():
    return render_template('index.html')

@app.route('/buy_order', methods=['POST'])
def buy_order():
    name = request.form['name']
    quantity = request.form['quantity']
    new_stock = Stock(name=name, quantity=int(quantity))
    db.session.add(new_stock)
    db.session.commit()
    return redirect('/stock_view')

@app.route('/stock_view', methods=['GET'])
def stock_view():
    all_stocks = Stock.query.all()
    return render_template('stock_view.html', stocks=all_stocks)

if __name__ == '__main__':
    app.run(debug=True)