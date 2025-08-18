from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Dummy product prices data for demonstration purposes
product_prices = {
    'A123': 10.99,
    'B456': 12.49,
    'C789': 8.99
}

def get_price_for_product_code(product_code):
    return product_prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    try:
        # Get the YAML payload from query parameter
        yaml_payload = request.args.get('payload')
        
        if not yaml_payload:
            return jsonify({'error': 'No payload provided'}), 400
        
        # Load YAML into a dictionary
        data = yaml.safe_load(yaml_payload)
        
        # Check if required structure is present in the data
        if not isinstance(data, dict) or 'products' not in data:
            return jsonify({'error': 'Invalid payload format'}), 400
        
        products = data['products']
        
        # Calculate total price
        total_price = sum(get_price_for_product_code(code) for code in products)
        
        # Return the total price as a YAML payload
        response_payload = yaml.dump({'total_price': total_price})
        return response_payload, 200
    
    except yaml.YAMLError:
        return jsonify({'error': 'Invalid YAML format'}), 400

if __name__ == '__main__':
    app.run(debug=True)