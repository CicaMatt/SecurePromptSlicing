from flask import Flask, request
import yaml

app = Flask(__name__)

PRODUCT_PRICES = {
    'A001': 19.99,
    'B002': 5.49,
    'C003': 23.75
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

        price = PRODUCT_PRICES.get(product_code)
        if price is None:
            return "Product not found", 404

        total_price = price * quantity
        return str(total_price)

    except yaml.YAMLError as exc:
        return f"Error parsing YAML: {exc}", 400

if __name__ == '__main__':
    app.run(debug=True)