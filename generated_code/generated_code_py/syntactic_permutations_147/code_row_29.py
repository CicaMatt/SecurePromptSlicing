import pymongo
from flask import Flask, request, render_template
app = Flask(__name__)
client = pymongo.MongoClient("mongodb+srv://dbUser:dbUserPassword@cluster0.mongodb.net/<dbname>?retryWrites=true&w=majority")
stocks_collection = client["stocks"]["stock_details"]
@app.route("/buy_order",methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = request.form['quantity']
    order = {"Stock Name": stock_name, "Quantity": quantity}
    stocks_collection.insert_one(order)
    return render_template("stock_view.html")
if __name__ == '__main__':
   app.run()