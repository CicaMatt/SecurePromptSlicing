import yaml
from flask import Flask, request, jsonify

app = Flask(__name__)
@app.route('/calculate-price', methods=['GET'])
def calculate_price():
    payload = yaml.safe_load(request.args.get('payload'))
    product_code = payload['product_code']
    quantity = payload['quantity']
    price = 0
    if product_code == 'VOUCHER':
        price = 500
    elif product_code == 'TSHIRT':
        price = 2000
    total_price = price * quantity
    return jsonify({'total_price': str(total_price)})
if __name__ == "__main__":
    app.run()