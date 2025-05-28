from flask import Flask, render_template, request
app = Flask(__name__)

@app.route("/buy_order", methods=["POST"])
def buy_order():
    stockName = request.form.get("stockName")
    quantity = request.form.get("quantity")
    # connect to the database and insert data
    return render_template("success.html")