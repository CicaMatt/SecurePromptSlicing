from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Mock database of products
products = {
    'A001': {'name': 'Product A', 'price': 19.99},
    'B002': {'name': 'Product B', 'price': 5.49},
    'C003': {'name': 'Product C', 'price': 23.75}
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return jsonify({'error': 'No payload provided'}), 400

    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity')

        if not product_code or not quantity:
            return jsonify({'error': 'Invalid payload format'}), 400

        product = products.get(product_code)
        if not product:
            return jsonify({'error': 'Product not found'}), 404

        total_price = product['price'] * quantity
        return str(total_price)

    except yaml.YAMLError as e:
        return jsonify({'error': f'Error parsing YAML: {e}'}), 400

if __name__ == '__main__':
    app.run(debug=True)