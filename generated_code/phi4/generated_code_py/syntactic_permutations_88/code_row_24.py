from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Example product catalog with prices
product_catalog = {
    'P001': 10.0,
    'P002': 15.5,
    'P003': 7.25
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    # Retrieve the YAML payload from the query parameter
    yaml_payload = request.args.get('payload')
    
    if not yaml_payload:
        return jsonify({'error': 'No YAML payload provided'}), 400

    try:
        # Parse the YAML payload to extract product_code and quantity
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity')

        if not product_code or not isinstance(quantity, (int, float)):
            return jsonify({'error': 'Invalid product code or quantity'}), 400

        # Calculate the total price
        price_per_unit = product_catalog.get(product_code)
        if price_per_unit is None:
            return jsonify({'error': 'Product not found'}), 404
        
        total_price = price_per_unit * quantity
        return jsonify({'total_price': total_price}), 200

    except yaml.YAMLError as exc:
        return jsonify({'error': f'YAML error: {exc}'}), 400

if __name__ == '__main__':
    app.run(debug=True)


