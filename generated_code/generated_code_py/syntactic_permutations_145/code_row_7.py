import sqlalchemy
from flask import Flask, render_template, request

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///stocks.db'
db = sqlalchemy.ext.declarative()

class Stock(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    stock_name = db.Column(db.String(100), nullable=False)
    quantity = db.Column(db.Integer, nullable=False)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/buy", methods=["POST"])
def buy_stock():
    stock_name = request.form["stock-name"]
    quantity = int(request.form["quantity"])
    buy_function(stock_name)
    return render_template("index.html", message="Stock bought successfully!")

def buy_function(stock_name):
    stock = Stock.query.filter_by(stock_name=stock_name).first()
    stock.quantity += quantity
    db.session.commit()
