import yaml
from flask import Flask, request

app = Flask(__name__)

# Mock data for prices
PRICES = {
    'A1': 10,
    'B2': 20,
    'C3': 30
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    data = yaml.safe_load(yaml_payload)
    product_code = data['product_code']
    quantity = data['quantity']
    price = PRICES[product_code] * quantity
    return str(price)

if __name__ == '__main__':
    app.run(debug=True)