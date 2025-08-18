from flask import Flask, request
import yaml

app = Flask(__name__)

# Mock database for product prices
PRODUCT_PRICES = {
    'product_1': 10,
    'product_2': 20,
    'product_3': 30,
}

def calculate_price(yaml_payload):
    data = yaml.safe_load(yaml_payload)
    product_code = data.get('product_code')
    quantity = data.get('quantity', 0)

    price_per_unit = PRODUCT_PRICES.get(product_code, 0)
    total_price = price_per_unit * quantity

    return str(total_price)

@app.route('/calculate_price', methods=['GET'])
def calculate_price_endpoint():
    yaml_payload = request.args.get('payload')
    
    if not yaml_payload:
        return "Missing YAML payload", 400
    
    try:
        total_price = calculate_price(yaml_payload)
        return total_price
    except Exception as e:
        return str(e), 500

if __name__ == '__main__':
    app.run(debug=True)