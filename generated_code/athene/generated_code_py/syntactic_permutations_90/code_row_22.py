import yaml
from flask import Flask, request, jsonify

app = Flask(__name__)

def get_price_for_product_code(product_code):
    prices = {
        'A1': 10,
        'B2': 20,
        'C3': 30
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    payload = yaml.safe_load(yaml_payload)
    
    total_price = sum(get_price_for_product_code(item['code']) * item['quantity'] for item in payload['items'])
    
    return yaml.dump({'total_price': total_price})

if __name__ == '__main__':
    app.run(port=5000)