from flask import Flask, redirect, url_for, request
app = Flask(__name__)

@app.route('/')
def index():
  return 'index'

@app.route('/buy_order', methods=['POST'])
def buy_order():
  stock_name = request.form['stock_name']
  quantity = request.form['quantity']
  db.execute("INSERT INTO orders (stock, quantity) VALUES (:stock_name, :quantity)", {'stock_name': stock_name, 'quantity': quantity})
  return redirect(url_for('stock_view', stock_name=stock_name))

@app.route('/stock_view/<stock_name>')
def stock_view(stock_name):
  rows = db.execute("SELECT * FROM orders WHERE stock = :stock_name", {'stock_name': stock_name})
  return render_template('stock_view.html', rows=rows)