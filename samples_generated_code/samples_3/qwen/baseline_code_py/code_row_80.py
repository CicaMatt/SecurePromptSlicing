from flask import Flask, request
import yaml

app = Flask(__name__)

# Mock database of products with their prices
product_prices = {
    'A001': 29.99,
    'B002': 45.50,
    'C003': 19.75
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return "No payload provided", 400

    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity')

        if not product_code or not quantity:
            return "Invalid payload", 400

        price = product_prices.get(product_code)
        if price is None:
            return f"Product code {product_code} not found", 404

        total_price = price * quantity
        return str(total_price)

    except yaml.YAMLError as e:
        return f"Error parsing YAML: {e}", 400

if __name__ == '__main__':
    app.run(debug=True)