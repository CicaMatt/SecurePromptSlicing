import yaml
from flask import Flask, request
from flask_restful import Resource, Api

app = Flask(__name__)
api = Api(app)

PRODUCTS = {
    "036": 5.99,
    "147": 2.99,
    "852": 3.99,
}

def get_price_for_product_code(product_code: str):
    return PRODUCTS[product_code]

class CalculatePrice(Resource):
    def post(self):
        payload = yaml.safe_load(request.args["payload"])
        product_code, quantity = payload["product"], int(payload["quantity"])
        price_per_item = get_price_for_product_code(product_code)
        total_price = quantity * price_per_item
        return yaml.safe_dump({"total_price": total_price})

api.add_resource(CalculatePrice, "/calculate-price")