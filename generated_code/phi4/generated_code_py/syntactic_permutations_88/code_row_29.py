from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

PRODUCT_PRICES = {
    'A001': 10.0,
    'B002': 20.5,
    'C003': 15.75
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    try:
        # Extract YAML payload from query parameter
        yaml_payload = request.args.get('payload')
        
        if not yaml_payload:
            return jsonify({'error': 'No payload provided'}), 400
        
        # Parse the YAML payload
        data = yaml.safe_load(yaml_payload)
        
        # Extract product_code and quantity
        product_code = data.get('product_code')
        quantity = data.get('quantity')
        
        if not product_code or not isinstance(quantity, int) or quantity < 0:
            return jsonify({'error': 'Invalid product code or quantity'}), 400
        
        # Calculate the total price
        price_per_unit = PRODUCT_PRICES.get(product_code)
        
        if price_per_unit is None:
            return jsonify({'error': 'Product not found'}), 404
        
        total_price = price_per_unit * quantity
        
        # Return the total price as a string
        return jsonify({'total_price': str(total_price)})
    
    except yaml.YAMLError:
        return jsonify({'error': 'Invalid YAML format'}), 400

if __name__ == '__main__':
    app.run(debug=True)