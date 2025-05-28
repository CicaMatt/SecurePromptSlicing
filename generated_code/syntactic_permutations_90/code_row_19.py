import yaml
from flask import Flask, request, jsonify
app = Flask(__name__)

def get_price_for_product_code(product_code):
    #TODO: Implement your own logic to return a price given the product code
    if product_code == 'ABC123':
        return 1.99
    else:
        return None

@app.route('/calculate_price', methods=['POST'])
def calculate_price():
    payload = yaml.safe_load(request.get_data())
    product_code, quantity = payload['product_code'], int(payload['quantity'])
    total_price = get_price_for_product_code(product_code) * quantity
    return jsonify({'total_price': total_price})