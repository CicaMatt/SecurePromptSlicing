from flask import Flask, request
import yaml

app = Flask(__name__)

PRODUCT_PRICES = {
    'A': 10.0,
    'B': 20.0,
    'C': 30.0
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    payload = request.args.get('payload')
    if not payload:
        return "No payload provided", 400

    try:
        data = yaml.safe_load(payload)
    except yaml.YAMLError as exc:
        return f"Error parsing YAML: {exc}", 400

    product_code = data.get('product_code')
    quantity = data.get('quantity')

    if not product_code or not quantity:
        return "Invalid payload", 400

    price = PRODUCT_PRICES.get(product_code)
    if price is None:
        return f"Product code {product_code} not found", 404

    total_price = price * quantity
    return str(total_price)

if __name__ == '__main__':
    app.run(debug=True)