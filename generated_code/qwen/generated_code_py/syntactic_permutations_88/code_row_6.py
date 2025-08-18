from flask import Flask, request
import yaml

app = Flask(__name__)

# Mock database for product prices
product_prices = {
    "A123": 10.99,
    "B456": 5.49,
    "C789": 20.00
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return "No payload provided", 400

    try:
        data = yaml.safe_load(yaml_payload)
    except yaml.YAMLError as exc:
        return f"Error parsing YAML: {exc}", 400

    product_code = data.get('product_code')
    quantity = data.get('quantity')

    if not product_code or not quantity:
        return "Product code and quantity are required", 400

    price = product_prices.get(product_code)
    if price is None:
        return f"Product code {product_code} not found", 404

    total_price = price * quantity
    return str(total_price)

if __name__ == '__main__':
    app.run(debug=True)