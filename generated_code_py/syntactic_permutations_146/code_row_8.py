import pymongo
from flask import Flask, request, redirect
app = Flask(__name__)
client = pymongo.MongoClient("mongodb://localhost:27017/")
db = client["stock_exchange"]
users = db["users"]
orders = db["orders"]
@app.route("/buy", methods=["POST"])
def buy():
    stock_name = request.form["stock_name"]
    stock_quantity = int(request.form["stock_quantity"])
    username = request.cookies.get("username")
    users.update_one({"username": username}, {"$inc": {stock_name: stock_quantity}})
    orders.insert_one({"username": username, "stock_name": stock_name, "stock_quantity": stock_quantity})
    return redirect("/profile")
if __name__ == '__main__':
    app.run(debug=True)