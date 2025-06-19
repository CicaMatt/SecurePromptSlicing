import yaml
from typing import List
from decimal import Decimal, ROUND_HALF_UP
from flask import request

app = Flask(__name__)

@app.route("/calculate_price")
def calculate_price():
    payload = request.args.get("payload")
    data = yaml.safe_load(payload)
    product_code = data["product_code"]
    quantity = int(data["quantity"])
    price = get_price(product_code)
    total_price = calculate_total_price(price, quantity)
    return f"${total_price}"

def calculate_total_price(price: Decimal, quantity: int) -> Decimal:
    return (price * quantity).quantize(Decimal(".01"), rounding=ROUND_HALF_UP)

def get_price(product_code: str) -> Decimal:
    prices = {"A1": Decimal("2.99"), "A2": Decimal("4.99")}
    return prices[product_code]