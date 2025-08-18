from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # This is a mock implementation. In a real scenario, this could fetch the price from a database.
    prices = {
        'A001': 19.99,
        'B002': 5.49,
        'C003': 7.89
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
        return jsonify({'error': f'YAML error: {exc}'}), 400

    product_code = data.get('product_code')
    quantity = data.get('quantity')

    if not product_code or not quantity:
        return jsonify({'error': 'Product code and quantity are required'}), 400

    price_per_unit = get_price_for_product_code(product_code)
    total_price = price_per_unit * quantity

    response = yaml.dump({'total_price': total_price})
    return response, 200, {'Content-Type': 'application/yaml'}

if __name__ == '__main__':
    app.run(debug=True)