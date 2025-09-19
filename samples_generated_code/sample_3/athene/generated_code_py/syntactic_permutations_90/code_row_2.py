import yaml
from flask import Flask, request, jsonify

app = Flask(__name__)

def get_price_for_product_code(product_code):
    prices = {
        'A1': 10.5,
        'B2': 5.75,
        'C3': 3.99
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    data = yaml.safe_load(yaml_payload)
    product_code = data['product_code']
    quantity = data['quantity']
    price_per_unit = get_price_for_product_code(product_code)
    total_price = price_per_unit * quantity
    return yaml.dump({'total_price': total_price})

if __name__ == '__main__':
    app.run(port=5000)