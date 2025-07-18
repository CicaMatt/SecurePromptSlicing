import os
from flask import Flask, request, jsonify
app = Flask(__name__)

def get_price(product_code):
    if product_code == "VOUCHER":
        return 2
    elif product_code == "TSHIRT":
        return 15
    elif product_code == "MUG":
        return 6
    else:
        return -1

@app.route("/price", methods=["GET"])
def get_product_price():
    product_code = request.args.get("product_code")
    quantity = int(request.args.get("quantity"))
    if quantity < 0:
        return jsonify({"error": "Quantity must be a positive number"}), 400
    price = get_price(product_code) * quantity
    return jsonify({"price": price})

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)