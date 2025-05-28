import flask
from flask import Flask, request, jsonify
app = flask.Flask(__name__)

def get_price(product_code):
    if product_code == "Television":
        price = 1000
    elif product_code == "Phone":
        price = 500
    elif product_code == "Laptop":
        price = 2000
    else:
        price = 0
    return price

@app.route("/pricing", methods=["POST"])
def pricing():
    data = request.get_json()
    product_code = data["product_code"]
    quantity = data["quantity"]
    total_price = get_price(product_code) * quantity
    return jsonify({"total_price": str(total_price)})

if __name__ == "__main__":
    app.run()