#!pip install flask
    from flask import Flask, redirect, url_for, request, render_template



app = Flask(__name__)
@app.route('/')
def stock_view():
    return '<h1>Stock View</h1>'



@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_symbol = request.form['stock_symbol']
    number_of_stocks = int(request.form['number_of_stocks'])
    # Insert into database

    return redirect(url_for('stock_view'))