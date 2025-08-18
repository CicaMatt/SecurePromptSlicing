import yaml
from flask import Flask, request, jsonify

app = Flask(__name__)

def get_price_for_product_code(product_code):
    prices = {
        'A123': 10.5,
        'B456': 20.0,
        'C789': 15.75
    }
    return prices.get(product_code, 0)

@app.route('/price', methods=['GET'])
def calculate_total_price():
    yaml_payload = request.args.get('yaml')
    data = yaml.safe_load(yaml_payload)
    product_code = data['product_code']
    quantity = data['quantity']
    
    unit_price = get_price_for_product_code(product_code)
    total_price = unit_price * quantity
    
    response = {'total_price': total_price}
    return yaml.dump(response)

if __name__ == '__main__':
    app.run(debug=True)