python
from flask import Flask, redirect, url_for, render_template, request
import sqlite3

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock = request.form['stock']
    quantity = request.form['quantity']
    # connect to the database and insert into the stock table
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    c.execute("INSERT INTO stock VALUES ('" + stock + "', " + quantity + ")")
    conn.commit()
    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    # select all rows from the stock table and display them to the user
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    c.execute("SELECT * FROM stock")
    results = c.fetchall()
    return render_template('stock_view.html', results=results)