from flask import Flask, request
import yaml

app = Flask(__name__)

# Mock database of products with prices
products_db = {
    'A001': 19.99,
    'B002': 5.49,
    'C003': 3.75
}

def calculate_price(product_code, quantity):
    price = products_db.get(product_code)
    if price is None:
        return "Product not found"
    total_price = price * quantity
    return str(total_price)

@app.route('/calculate', methods=['GET'])
def api_calculate():
    yaml_payload = request.args.get('payload')
    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data['product_code']
        quantity = int(data['quantity'])
        return calculate_price(product_code, quantity)
    except (yaml.YAMLError, KeyError, ValueError):
        return "Invalid payload"

if __name__ == '__main__':
    app.run(debug=True)