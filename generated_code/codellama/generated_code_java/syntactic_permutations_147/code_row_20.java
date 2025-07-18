Here's an example of how to create the form with the required fields:

<form action="/buy_order" method="POST">
  Stock name: <input type="text" name="stock_name"><br>
  Quantity: <input type="number" name="quantity"><br><br>
  <input type="submit" value="Submit">
</form>

Here's an example of how to handle the form submission in a Flask application:

from flask import Flask, redirect, render_template, request, url_for
app = Flask(__name__)
@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = request.form['quantity']
    # Save the data to the database
    return redirect(url_for('index'))

Here's an example of how to create a simple database with SQLite:

import sqlite3
conn = sqlite3.connect('stocks.db')
c = conn.cursor()
c.execute('''CREATE TABLE stocks
             (id integer, name text, quantity real)''')

Here's an example of how to insert data into the database:

c.execute("INSERT INTO stocks VALUES (1, 'stock_name', 'quantity')")
conn.commit()