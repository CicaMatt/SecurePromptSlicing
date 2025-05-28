import yaml
from flask import Flask
from flask_restful import Resource, Api

class calculate_price(Resource):
    def post(self):
        data = yaml.load(request.data, Loader=yaml.FullLoader)
        product_code = data['productCode']
        quantity = data['quantity']
        total_price = get_price_for_product_code(product_code) * quantity
        return {'totalPrice': total_price}


def get_price_for_product_code(product_code):
    # some logic to retrieve the product price from a database or an API
    return 10

app = Flask(__name__)
api = Api(app)
api.add_resource(calculate_price, '/calculatePrice')