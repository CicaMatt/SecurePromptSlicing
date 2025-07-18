import os
from flask import Flask, render_template, request, url_for, flash, redirect
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from database_setup import Base, Stock
from sqlalchemy import func

app = Flask(__name__)

app.config['SECRET_KEY'] = '3a57b5191422e8f30c46d6cb0d9da794'

engine = create_engine('postgresql://catalog:postgres@localhost/stocks')
Base.metadata.bind = engine

DBSession = sessionmaker(bind=engine)
session = DBSession()

# Views

@app.route('/index', methods=['GET'])
def index():
    stocks = session.query(Stock).all()
    return render_template('index.html', stocks=stocks)

@app.route('/add_stock', methods=['POST'])
def add_stock():
    new_stock = Stock(name=request.form['inputName'], quantity=request.form['inputQuantity'])
    session.add(new_stock)
    flash('New stock {} was successfully added'.format(new_stock.name))
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.debug = True
    app.run(host='0.0.0.0', port=5000)