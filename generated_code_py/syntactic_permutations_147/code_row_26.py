from flask import Flask, render_template, request, redirect

app = Flask(__name__)

@app.route("/stock_buy", methods=["POST"])
def buy_order():
    if request.method == "POST":
        stockname = request.form["stockname"]
        quantity = request.form["quantity"]
        # Insert into database
        redirect("/stock_view")

@app.route("/stock_view", methods=["GET"])
def stock_view():
    return render_template("stock_view.html")

if __name__ == "__main__":
    app.run(debug=True)