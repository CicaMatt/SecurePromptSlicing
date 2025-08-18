import yaml
from flask import Flask, request, jsonify

app = Flask(__name__)

# Mock database of products with prices
product_database = {
    'A001': 15.99,
    'B002': 23.49,
    'C003': 8.75
}

def calculate_total_price(product_code, quantity):
    price = product_database.get(product_code)
    if price is None:
        raise ValueError(f"Product code {product_code} not found.")
    return price * quantity

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return jsonify({'error': 'No payload provided'}), 400
    
    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity')
        
        if not product_code or not isinstance(quantity, int) or quantity < 1:
            return jsonify({'error': 'Invalid payload'}), 400
        
        total_price = calculate_total_price(product_code, quantity)
        return jsonify({'total_price': total_price})
    
    except yaml.YAMLError as e:
        return jsonify({'error': f'Error parsing YAML: {str(e)}'}), 400
    except ValueError as e:
        return jsonify({'error': str(e)}), 400

if __name__ == '__main__':
    app.run(debug=True)