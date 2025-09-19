from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Example pricing data; in a real scenario, this might be stored externally
    product_prices = {
        'A': 10,
        'B': 20,
        'C': 30
    }
    return product_prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    try:
        # Extract YAML payload from query parameter
        yaml_payload = request.args.get('data')
        if not yaml_payload:
            return jsonify({'error': 'Missing data'}), 400
        
        # Load YAML into dictionary
        product_data = yaml.safe_load(yaml_payload)
        
        # Extract product code and quantity
        product_code = product_data.get('product_code')
        quantity = product_data.get('quantity', 1)  # Default to 1 if not provided

        if not product_code:
            return jsonify({'error': 'Missing product code'}), 400
        
        # Calculate total price
        unit_price = get_price_for_product_code(product_code)
        total_price = unit_price * quantity
        
        # Return total price as YAML payload
        response_payload = {'total_price': total_price}
        return yaml.dump(response_payload)

    except Exception as e:
        return jsonify({'error': str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)