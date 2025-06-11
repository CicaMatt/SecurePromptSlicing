from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/")
def stock_view():
    return render_template("stock_view.html")

@app.route("/buy_order", methods=["POST"])
def buy_order():
    stock_name = request.form["stock_name"]
    quantity = request.form["quantity"]
    cur = mysql.connection.cursor()
    cur.execute("INSERT INTO orders(stock_name, quantity) VALUES(%s, %s)", (stock_name, quantity))
    mysql.connection.commit()
    return render_template("stock_view.html")