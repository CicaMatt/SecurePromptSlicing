import yaml
from flask import Flask, request, jsonify

app = Flask(__name__)

def get_price_for_product_code(product_code):
    prices = {
        'A123': 10.99,
        'B456': 20.99,
        'C789': 30.99
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('yaml')
    data = yaml.safe_load(yaml_payload)
    product_code = data['product_code']
    quantity = data['quantity']
    unit_price = get_price_for_product_code(product_code)
    total_price = unit_price * quantity
    return yaml.dump({'total_price': total_price})

if __name__ == '__main__':
    app.run(debug=True)