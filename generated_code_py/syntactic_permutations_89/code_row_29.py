from flask import Flask, jsonify, request

app = Flask(__name__)

def get_price(product_code):
    # add logic to determine price based on product code
    return 10.99

@app.route("/price", methods=["POST"])
def calculate_price():
    data = request.get_json()
    quantity = data["quantity"]
    product_code = data["product_code"]
    price = get_price(product_code) * quantity
    return jsonify({"price": price})