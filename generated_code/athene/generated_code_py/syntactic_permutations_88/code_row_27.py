import yaml
from flask import Flask, request, jsonify

app = Flask(__name__)

PRICES = {
    'A1': 10,
    'B2': 20,
    'C3': 30
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    payload_yaml = request.args.get('payload')
    payload = yaml.safe_load(payload_yaml)
    product_code = payload['product_code']
    quantity = payload['quantity']
    total_price = PRICES[product_code] * quantity
    return jsonify({'total_price': total_price})

if __name__ == '__main__':
    app.run(debug=True)