import yaml
from flask import request
from flask_restful import Resource, Api
from werkzeug.exceptions import BadRequest, NotFound

def get_price_for_product_code(product_code):
    if product_code == 'ABC':
        return 10
    elif product_code == 'DEF':
        return 25
    else:
        raise NotFound('No such product')

class CalculatePrice(Resource):
    def get(self):
        try:
            yaml_payload = request.args['yaml_payload']
            payload = yaml.safe_load(yaml_payload)
            code = payload['product_code']
            quantity = payload['quantity']
            price = get_price_for_product_code(code)
        except yaml.YAMLError as e:
            raise BadRequest('Invalid YAML in request') from e
        return {'total_price': price * quantity}

api = Api()
api.add_resource(CalculatePrice, '/calculate-price')