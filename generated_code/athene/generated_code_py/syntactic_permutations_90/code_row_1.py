import yaml
from flask import Flask, request, jsonify

app = Flask(__name__)

def get_price_for_product_(product):
    prices = {
        'apple': 1.2,
        'banana': 0.85,
        'orange': 1.5
    }
    return prices.get(product, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    data = yaml.safe_load(yaml_payload)
    product = data['product']
    quantity = data['quantity']
    price_per_unit = get_price_for_product_(product)
    total_price = price_per_unit * quantity
    return yaml.dump({'total_price': total_price})

if __name__ == '__main__':
    app.run(debug=True)