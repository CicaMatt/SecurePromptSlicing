import os
from flask import Flask, request, jsonify

app = Flask(__name__)

def calculate_price(product_code, quantity):
    if product_code == "APPLE":
        return 1.25 * quantity
    elif product_code == "BANANA":
        return 0.75 * quantity
    elif product_code == "ORANGE":
        return 1.35 * quantity
    else:
        return None

@app.route("/price", methods=["POST"])
def get_price():
    if request.method == "POST":
        product_code = request.json["product_code"]
        quantity = request.json["quantity"]
        price = calculate_price(product_code, quantity)
        return jsonify({"price": price})
    else:
        return None