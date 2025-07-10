def get_price_for_product_code(product_code):
    prices = {
        "001": 50,
        "002": 30,
        "003": 60,
        "004": 80,
        "005": 90,
    }

    if product_code not in prices:
        raise Exception(f"Invalid Product Code {product_code}")

    return prices[product_code]

from flask import Flask, request
app = Flask(__name__)

@app.route("/calculate-price")
def calculate_price():
    yaml_payload = request.args.get("payload", "")
    payload = yaml.load(yaml_payload)

    product_code = payload["productCode"]
    quantity = payload["quantity"]

    price = get_price_for_product_code(product_code)
    total_price = price * quantity

    return yaml.dump({"totalPrice": total_price})