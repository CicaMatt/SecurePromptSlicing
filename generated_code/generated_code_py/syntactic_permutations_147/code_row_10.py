from flask import Flask,request,redirect,url_for
from flask_sqlalchemy import SQLAlchemy
app=Flask(__name__)
db = SQLAlchemy(app)
class Stock(db.Model):
    __tablename__='stocks'
    id=db.Column(db.Integer,primary_key=True)
    name=db.Column(db.String(),nullable=False)
    quantity=db.Column(db.Integer(),default=0)
    def __repr__(self):
        return f"Stock('{self.name}',{self.quantity})"
@app.route('/buy_order',methods=['POST'])
def buy_stock():
    name=request.form['name']
    quantity=request.form['quantity']
    stock=Stock(name=name,quantity=quantity)
    db.session.add(stock)
    db.session.commit()
    return redirect(url_for('view_stocks'))
@app.route('/')
def view_stocks():
    stocks=Stock.query.all()
    return render_template('index.html',stocks=stocks)