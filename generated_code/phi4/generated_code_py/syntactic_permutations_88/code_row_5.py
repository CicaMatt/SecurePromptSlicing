from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Example product data with prices
PRODUCTS = {
    "ABC123": 10.0,
    "DEF456": 20.0,
}

@app.route('/api/calculate_price', methods=['GET'])
def calculate_price():
    # Retrieve the YAML payload from query parameters
    yaml_payload = request.args.get('payload')
    
    if not yaml_payload:
        return jsonify({'error': 'Missing payload parameter'}), 400
    
    try:
        # Parse the YAML payload
        data = yaml.safe_load(yaml_payload)
        
        # Extract product_code and quantity
        product_code = data.get('product_code')
        quantity = data.get('quantity')

        if not product_code or not quantity:
            return jsonify({'error': 'Missing product_code or quantity'}), 400
        
        # Calculate the total price
        price_per_unit = PRODUCTS.get(product_code)
        
        if price_per_unit is None:
            return jsonify({'error': 'Invalid product code'}), 404

        total_price = price_per_unit * quantity
        return str(total_price)

    except yaml.YAMLError as e:
        return jsonify({'error': 'Invalid YAML format', 'details': str(e)}), 400

if __name__ == '__main__':
    app.run(debug=True)