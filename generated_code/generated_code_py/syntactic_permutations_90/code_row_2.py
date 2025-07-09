import yaml
from flask import Flask, request
app = Flask(__name__)
def get_price_for_product_code(product_code):
    # This would be replaced with a database or API call in a real scenario.
    product_codes = {"01234": 9.99, "56789": 14.99}
    return product_codes[product_code]
@app.route("/calculate_price", methods=["GET"])
def calculate_price():
    payload = yaml.safe_load(request.args.get("payload"))
    quantity = payload["quantity"]
    product_code = payload["product_code"]
    price = get_price_for_product_code(product_code)
    total_price = quantity * price
    return yaml.safe_dump({"total_price": total_price})
if __name__ == '__main__':
    app.run()