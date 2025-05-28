import yaml
from flask import Flask
from flask import request
app = Flask(__name__)

product_code_to_price = {
    'VOUCHER': 5.0,
    'TSHIRT': 20.0,
    'MUG': 7.50
}

@app.route('/calculate-price', methods=['GET'])
def calculate_price():
    query_parameters = request.args
    payload = yaml.load(query_parameters['payload'], Loader=yaml.FullLoader)

    product_code = payload['product_code']
    quantity = payload['quantity']

    price = get_price_for_product_code(product_code) * quantity

    return yaml.dump({'total_price': price})

def get_price_for_product_code(product_code):
    if product_code not in product_code_to_price:
        raise ValueError('Invalid product code')
    
    return product_code_to_price[product_code]