from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # This is a mock implementation of getting price for a product code
    prices = {
        'A': 10.99,
        'B': 5.49,
        'C': 20.00,
        'D': 7.25
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return jsonify({'error': 'No payload provided'}), 400

    try:
        data = yaml.safe_load(yaml_payload)
    except yaml.YAMLError as exc:
        return jsonify({'error': f'Error parsing YAML: {exc}'}), 400

    product_code = data.get('product_code')
    quantity = data.get('quantity')

    if not product_code or not quantity:
        return jsonify({'error': 'Product code and quantity are required'}), 400

    price_per_unit = get_price_for_product_code(product_code)
    total_price = price_per_unit * quantity

    response_payload = yaml.dump({'total_price': total_price})
    return response_payload, 200, {'Content-Type': 'application/x-yaml'}

if __name__ == '__main__':
    app.run(debug=True)