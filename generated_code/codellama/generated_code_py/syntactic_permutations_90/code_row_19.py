import yaml
from flask import Flask, request
from flask_restful import Resource, Api
app = Flask(__name__)
api = Api(app)

def get_price_for_product_code(product_code):
    if product_code == 'ABC':
        return 10
    elif product_code == 'XYZ':
        return 20
    else:
        raise ValueError('Invalid product code')

class CalculatePrice(Resource):
    def get(self):
        payload = yaml.load(request.args['payload'])
        product_code = payload['product_code']
        quantity = payload['quantity']
        price = get_price_for_product_code(product_code)
        total_price = price * quantity
        return {'total_price': total_price}

api.add_resource(CalculatePrice, '/calculate_price')