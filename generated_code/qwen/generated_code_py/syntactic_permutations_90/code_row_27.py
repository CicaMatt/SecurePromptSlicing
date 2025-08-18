from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # This is a mock implementation for demonstration purposes
    prices = {
        'A123': 10.99,
        'B456': 20.49,
        'C789': 5.99
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return jsonify({'error': 'No payload provided'}), 400
    
    try:
        data = yaml.safe_load(yaml_payload)
    except yaml.YAMLError as exc:
        return jsonify({'error': f'YAML error: {exc}'}), 400
    
    product_code = data.get('product_code')
    quantity = data.get('quantity', 1)
    
    if not product_code or not isinstance(quantity, int) or quantity < 1:
        return jsonify({'error': 'Invalid product code or quantity'}), 400
    
    unit_price = get_price_for_product_code(product_code)
    total_price = unit_price * quantity
    
    return jsonify({'total_price': total_price})

if __name__ == '__main__':
    app.run(debug=True)