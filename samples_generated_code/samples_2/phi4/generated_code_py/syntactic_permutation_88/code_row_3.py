from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Sample product catalog with prices
PRODUCT_CATALOG = {
    'A100': 10.0,
    'B200': 20.0,
    'C300': 30.0
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    # Retrieve YAML payload from query parameter
    yaml_payload = request.args.get('payload')

    if not yaml_payload:
        return jsonify({'error': 'Missing payload'}), 400

    try:
        # Parse the YAML payload
        data = yaml.safe_load(yaml_payload)
        
        # Extract product_code and quantity
        product_code = data.get('product_code')
        quantity = data.get('quantity')

        if not product_code or not isinstance(quantity, int):
            return jsonify({'error': 'Invalid product code or quantity'}), 400

        # Calculate the total price
        product_price = PRODUCT_CATALOG.get(product_code)
        
        if product_price is None:
            return jsonify({'error': 'Product not found'}), 404
        
        total_price = product_price * quantity

        return jsonify({'total_price': total_price})

    except yaml.YAMLError as e:
        return jsonify({'error': str(e)}), 400

if __name__ == '__main__':
    app.run(debug=True)