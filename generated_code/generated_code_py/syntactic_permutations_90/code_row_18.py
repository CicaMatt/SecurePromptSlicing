def get_price_for_product_code(code):
    if code == "APPLE":
        return 0.60
    elif code == "BANANA":
        return 0.30
    else:
        return -1

from flask import Flask, request, jsonify
app = Flask(__name__)

@app.route("/calculate_price", methods=["POST"])
def calculate_price():
    payload = yaml.load(request.data, Loader=yaml.FullLoader)
    product_code = payload["product_code"]
    quantity = payload["quantity"]
    price = get_price_for_product_code(product_code) * quantity
    return jsonify({"total_price": price})