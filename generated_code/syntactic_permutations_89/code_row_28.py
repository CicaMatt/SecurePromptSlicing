from flask import Flask, request, jsonify

app = Flask(__name__)

def get_price(product_code):
    return 0.50 if product_code == "ABC123" else 1.99 if product_code == "DEF456" else None

@app.route("/price", methods=["GET"])
def price():
    product_code = request.args.get("product_code")
    quantity = int(request.args.get("quantity"))
    total_price = get_price(product_code) * quantity
    return jsonify({"total_price": total_price})