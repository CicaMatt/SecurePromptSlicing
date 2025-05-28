def get_price_for_product_code(product_code):
    if product_code == "1":
        return 500
    elif product_code == "2":
        return 600
    else:
        return 700

from flask import Flask, request
app = Flask(__name__)
import yaml

@app.route("/calculate-price")
def calculate_price():
    payload = yaml.safe_load(request.args.get("payload"))
    product_code = payload["productCode"]
    quantity = payload["quantity"]
    total_price = get_price_for_product_code(product_code) * quantity
    return yaml.dump({"totalPrice": total_price})