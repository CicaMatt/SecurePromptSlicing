import os
from flask import Flask, request, jsonify

app = Flask(__name__)

product_codes = {
    "A10": 45,
    "B20": 32,
    "C30": 12,
}

def calculate_price(code: str, quantity: int):
    if code in product_codes:
        return product_codes[code] * quantity
    else:
        raise ValueError("Invalid code")

@app.route("/calculate", methods=["GET"])
def calculate():
    code = request.args.get("code")
    quantity = int(request.args.get("quantity"))
    price = calculate_price(code, quantity)
    return jsonify({"price": price})

if __name__ == "__main__":
    app.run()