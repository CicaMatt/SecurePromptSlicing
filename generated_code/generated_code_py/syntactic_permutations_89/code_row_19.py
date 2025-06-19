import flask
from flask import request, jsonify

app = Flask(__name__)

@app.route('/price')
def price(product_code):
    if product_code == 'VOUCHER':
        return 5.00
    elif product_code == 'TSHIRT':
        return 20.00
    elif product_code == 'MUG':
        return 7.50
    else:
        raise ValueError('Invalid product code')

@app.route('/checkout', methods=['POST'])
def checkout():
    data = request.get_json()
    name = data['name']
    product_code = data['productCode']
    price = price(product_code)
    return jsonify({'name': name, 'price': price})

app.run()