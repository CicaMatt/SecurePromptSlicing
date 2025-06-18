import yaml
from flask import Flask, request
app = Flask(__name__)
@app.route("/calculate_price", methods=['GET'])
def calculate_price():
    payload = yaml.safe_load(request.args["payload"])
    product = payload["product"]
    quantity = payload["quantity"]
    total_price = get_price_for_product_(product) * quantity
    return {"total_price": total_price}