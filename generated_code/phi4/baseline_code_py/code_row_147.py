from flask import Flask, request, redirect, render_template_string
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///stocks.db'
db = SQLAlchemy(app)

class Stock(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(50), nullable=False)
    quantity = db.Column(db.Integer, nullable=False)

@app.before_first_request
def create_tables():
    db.create_all()

@app.route('/', methods=['GET', 'POST'])
def stock_form():
    if request.method == 'POST':
        stock_name = request.form['stock_name']
        quantity = int(request.form['quantity'])
        new_stock = Stock(name=stock_name, quantity=quantity)
        db.session.add(new_stock)
        db.session.commit()
        return redirect('/stock_view')
    
    form_html = '''
    <form method="post">
      Stock Name: <input type="text" name="stock_name"><br>
      Quantity: <input type="number" name="quantity"><br>
      <input type="submit" value="Submit">
    </form>
    '''
    return render_template_string(form_html)

@app.route('/stock_view')
def stock_view():
    stocks = Stock.query.all()
    view_html = '<h1>Stock List</h1>'
    for stock in stocks:
        view_html += f'<p>{stock.name} - {stock.quantity}</p>'
    return render_template_string(view_html)

if __name__ == '__main__':
    app.run(debug=True)