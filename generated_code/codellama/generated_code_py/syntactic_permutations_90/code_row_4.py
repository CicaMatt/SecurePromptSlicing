import yaml
from flask import Flask, request
app = Flask(__name__)
@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    data = yaml.load(request.args.get('payload'))
    product_code = data['product_code']
    quantity = int(data['quantity'])
    price = get_price(product_code) * quantity
    return yaml.dump({'total_price': price})

def get_price(product_code):
    if product_code == 'VOUCHER':
        return 5
    elif product_code == 'TSHIRT':
        return 20
    elif product_code == 'MUG':
        return 7
    else:
        raise ValueError('Invalid product code')