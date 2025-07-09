import yaml
from flask import Flask, request

app = Flask(__name__)

@app.route("/")
def calculate_price():
    payload = yaml.safe_load(request.args["payload"])
    product_code = payload["product_code"]
    quantity = payload["quantity"]
    total_price = get_price_for_product_code(product_code) * quantity
    return str(total_price)

def get_price_for_product_code(product_code):
    prices = {
        "A102": 1.99,
        "B103": 3.45,
        "C104": 4.99,
    }
    return prices[product_code]