from flask import Flask, request, redirect
from pymongo import MongoClient
import bcrypt
app = Flask(__name__)
app.config["MONGO_URI"] = "mongodb://localhost:27017/stock"
client = MongoClient(app.config['MONGO_URI'])
db = client.stock
@app.route("/buy_order", methods=['POST'])
def buy_order():
    name = request.form["name"]
    quantity = request.form["quantity"]
    db.orders.insert_one({"name":name, "quantity":quantity})
    return redirect("/stock_view")
@app.route("/stock_view", methods=['GET'])
def stock_view():
    cursor = db.orders.find()
    return render_template("stock_view.html", cursor=cursor)
if __name__ == "__main__":
  app.run(debug=True)