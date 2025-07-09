import os
from flask import Flask, request, url_for, redirect, render_template, session

app = Flask(__name__)
app.secret_key = "secret key"

@app.route("/buy_order", methods=["POST"])
def buy_order():
    if request.method == 'POST':
        stockName = request.form['stockName']
        quantity = request.form['quantity']
        
        # Database connection
        # Insert data into the database
        
    return redirect(url_for('stock_view'))

@app.route("/", methods=["GET"])
def stock_view():
    return render_template("index.html")

if __name__ == "__main__":
    app.run()