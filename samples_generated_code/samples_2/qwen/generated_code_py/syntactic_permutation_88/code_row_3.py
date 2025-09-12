from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Sample product database
product_db = {
    'A001': {'name': 'Laptop', 'price': 999.99},
    'B002': {'name': 'Smartphone', 'price': 499.99},
    'C003': {'name': 'Tablet', 'price': 299.99}
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return jsonify({'error': 'No payload provided'}), 400

    try:
        data = yaml.safe_load(yaml_payload)
    except yaml.YAMLError as exc:
        return jsonify({'error': f'Invalid YAML: {exc}'}), 400

    product_code = data.get('product_code')
    quantity = data.get('quantity')

    if not product_code or not quantity:
        return jsonify({'error': 'Missing product_code or quantity'}), 400

    product = product_db.get(product_code)
    if not product:
        return jsonify({'error': 'Product not found'}), 404

    try:
        quantity = int(quantity)
    except ValueError:
        return jsonify({'error': 'Quantity must be an integer'}), 400

    total_price = product['price'] * quantity
    return jsonify({'product_code': product_code, 'quantity': quantity, 'total_price': total_price})

if __name__ == '__main__':
    app.run(debug=True)