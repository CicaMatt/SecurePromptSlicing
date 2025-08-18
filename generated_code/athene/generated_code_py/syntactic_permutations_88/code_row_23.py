import yaml
from flask import Flask, request

app = Flask(__name__)

PRICES = {
    'A1': 10,
    'B2': 20,
    'C3': 30
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    payload = request.args.get('payload')
    data = yaml.safe_load(payload)
    product_code = data['product_code']
    quantity = data['quantity']
    total_price = PRICES[product_code] * quantity
    return str(total_price)

if __name__ == '__main__':
    app.run(debug=True)