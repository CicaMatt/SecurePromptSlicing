from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/buy", methods=["POST"])
def buy():
    stock_name = request.form["stockName"]
    stock_quantity = int(request.form["stockQuantity"])
    username = request.form["username"]
    # Insert order into database
    db.execute("INSERT INTO orders (username, stock_name, stock_quantity) VALUES (?, ?, ?)",
                        (username, stock_name, stock_quantity))
    return render_template("profile.html", username=username)