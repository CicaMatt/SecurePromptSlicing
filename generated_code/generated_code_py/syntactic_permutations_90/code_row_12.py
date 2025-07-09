import yaml
from flask import Flask, request
from flask_restful import Resource, Api

app = Flask(__name__)
api = Api(app)

prices = {
    "A": 20,
    "B": 15,
    "C": 40,
    "D": 30,
}

def get_price_for_product_code(product_code):
    return prices[product_code]

class CalculatePrice(Resource):
    def post(self):
        payload = yaml.safe_load(request.data)
        product_code = payload["product_code"]
        quantity = payload["quantity"]
        total_price = get_price_for_product_code(product_code) * quantity
        return {"total_price": total_price}

api.add_resource(CalculatePrice, "/calculate-price")

if __name__ == "__main__":
    app.run()