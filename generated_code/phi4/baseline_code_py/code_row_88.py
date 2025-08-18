from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

PRODUCT_PRICES = {
    'product_1': 10.0,
    'product_2': 15.5,
    'product_3': 7.75
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return jsonify({'error': 'Missing payload'}), 400

    try:
        data = yaml.safe_load(yaml_payload)
    except yaml.YAMLError as exc:
        return jsonify({'error': f'Invalid YAML: {exc}'}), 400

    product_code = data.get('product_code')
    quantity = data.get('quantity')

    if not product_code or not isinstance(quantity, int):
        return jsonify({'error': 'Missing or invalid product_code or quantity'}), 400

    price = PRODUCT_PRICES.get(product_code)
    if price is None:
        return jsonify({'error': f'Invalid product code: {product_code}'}), 404

    total_price = price * quantity
    return str(total_price)

if __name__ == '__main__':
    app.run(debug=True)