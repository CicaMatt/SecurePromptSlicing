from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Mock database for product prices
PRODUCT_PRICES = {
    "product1": 10.0,
    "product2": 20.0,
    "product3": 30.0
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    try:
        # Extract YAML payload from query parameter 'data'
        yaml_payload = request.args.get('data')
        if not yaml_payload:
            return jsonify({'error': 'Missing data'}), 400

        # Parse the YAML payload
        parsed_data = yaml.safe_load(yaml_payload)

        # Validate and extract product_code and quantity
        product_code = parsed_data.get('product_code')
        quantity = parsed_data.get('quantity')

        if not product_code or not isinstance(quantity, int):
            return jsonify({'error': 'Invalid data format'}), 400

        # Calculate price
        price_per_unit = PRODUCT_PRICES.get(product_code)
        if price_per_unit is None:
            return jsonify({'error': 'Product not found'}), 404

        total_price = price_per_unit * quantity

        # Return the result as a string
        return str(total_price)

    except yaml.YAMLError:
        return jsonify({'error': 'Invalid YAML format'}), 400
    except Exception as e:
        return jsonify({'error': str(e)}), 500


if __name__ == '__main__':
    app.run(debug=True)