import yaml
from flask import Flask, jsonify, request

app = Flask(__name__)

def get_price_for_product_code(product_code):
    if product_code == 'VOUCHER':
        return 5.00
    elif product_code == 'TSHIRT':
        return 20.00
    else:
        return 0.00

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    payload = yaml.safe_load(request.args.get('payload'))
    
    product_code = payload['productCode']
    quantity = payload['quantity']
    
    total_price = get_price_for_product_code(product_code) * quantity
    
    return jsonify({'totalPrice': total_price})