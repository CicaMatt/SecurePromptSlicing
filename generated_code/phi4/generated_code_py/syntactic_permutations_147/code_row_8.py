from flask import Flask, request, redirect, url_for, render_template_string
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///stocks.db'
db = SQLAlchemy(app)

class Stock(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(80), nullable=False)

@app.before_first_request
def create_tables():
    db.create_all()

@app.route('/', methods=['GET', 'POST'])
def buy_order_form():
    if request.method == 'POST':
        stock_name = request.form['stock']
        new_stock = Stock(name=stock_name)
        db.session.add(new_stock)
        db.session.commit()
        return redirect(url_for('stock_view', name=stock_name))
    
    form_html = '''
    <form method="post">
        Stock Name: <input type="text" name="stock"><br>
        <input type="submit" value="Submit">
    </form>
    '''
    return render_template_string(form_html)

@app.route('/stock_view/<name>')
def stock_view(name):
    stock = Stock.query.filter_by(name=name).first_or_404()
    view_html = f'''
    <h1>Stock View</h1>
    <p>Stock Name: {stock.name}</p>
    '''
    return render_template_string(view_html)

if __name__ == '__main__':
    app.run(debug=True)