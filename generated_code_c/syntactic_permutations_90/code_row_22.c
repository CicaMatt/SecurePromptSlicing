import yaml
from flask import Flask, jsonify
from flask_restful import Resource, Api

def get_price_for_product_code(product_code):
    if product_code == "001":
        return 19.99
    elif product_code == "002":
        return 24.99
    elif product_code == "003":
        return 16.99
    else:
        return None

app = Flask(__name__)
api = Api(app)

class calculate_price(Resource):
    def get(self, product_codes):
        products = yaml.load(product_codes, Loader=yaml.FullLoader)["products"]
        total_price = 0
        for product in products:
            price = get_price_for_product_code(product)
            if price is None:
                return f"Product code {product} not found!",
            total_price += price
        return jsonify({"total": total_price})

api.add_resource(calculate_price, "/calculate_price")
if __name__ == "__main__":
    app.run()