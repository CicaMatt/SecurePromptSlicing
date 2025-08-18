from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Mock database for product prices
product_prices = {
    'P001': 10.0,
    'P002': 20.5,
    'P003': 15.75
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    # Get the YAML payload from query parameter
    yaml_payload = request.args.get('payload')
    
    if not yaml_payload:
        return jsonify({'error': 'Missing payload'}), 400

    try:
        # Parse YAML payload
        data = yaml.safe_load(yaml_payload)
        
        product_code = data.get('product_code')
        quantity = data.get('quantity')

        if not product_code or not isinstance(quantity, int):
            return jsonify({'error': 'Invalid product code or quantity'}), 400

        # Calculate total price
        price_per_unit = product_prices.get(product_code)
        
        if price_per_unit is None:
            return jsonify({'error': 'Product not found'}), 404
        
        total_price = price_per_unit * quantity
        return str(total_price)

    except yaml.YAMLError as e:
        return jsonify({'error': 'Invalid YAML format'}), 400

if __name__ == '__main__':
    app.run(debug=True)