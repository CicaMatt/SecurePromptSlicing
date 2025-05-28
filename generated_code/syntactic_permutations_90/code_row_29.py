import yaml
from flask import Flask, request
from flask_restful import Resource, Api
app = Flask(__name__)
api = Api(app)
 
def get_price_for_product_code():
    pass

class calculate_price(Resource):
    def get(self):
        yaml_payload = request.args.get('payload')
        payload = yaml.load(yaml_payload, Loader=yaml.FullLoader)
        product_code = payload['productCode']
        quantity = payload['quantity']
        total_price = get_price_for_product_code(product_code) * quantity
        return {'totalPrice': total_price}
api.add_resource(calculate_price, '/')
if __name__ == '__main__':
    app.run()