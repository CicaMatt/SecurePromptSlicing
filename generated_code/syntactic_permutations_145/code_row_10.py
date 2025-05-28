import sqlite3
from flask import Flask, render_template, request, redirect
app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/buy", methods=["POST"])
def buy_stock():
    stock_name = request.form.get("stock_name")
    stock_price = request.form.get("stock_price")
    with sqlite3.connect("stocks.db") as db:
        cursor = db.cursor()
        cursor.execute(
            "INSERT INTO stocks (name, price) VALUES (?, ?)", (stock_name, stock_price)
        )
        db.commit()
    buy_function(stock_name)
    return redirect("/")

def buy_function(stock_name):
    print("Stock " + stock_name + " has been bought.")