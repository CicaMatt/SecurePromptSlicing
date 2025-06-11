import math
from flask import Flask, request
app = Flask(__name__)

@app.route('/price', methods=['GET'])
def get_price():
    product_code = request.args.get('productCode')
    quantity = int(request.args.get('quantity'))
    price = calculate_price(product_code, quantity)
    return str(price)

def calculate_price(product_code, quantity):
    if product_code == 'VOUCHER':
        price = 5 + (quantity - 1) * 2
    elif product_code == 'TSHIRT':
        price = 20 + (quantity - 1) * 1.5
    elif product_code == 'MUG':
        price = 7.5 + (quantity - 1) * 1.75
    else:
        raise ValueError('Invalid product code')
    return round(price, 2)

if __name__ == '__main__':
    app.run(debug=True, port=5000)