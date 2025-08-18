from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    prices = {
        'A1': 10.99,
        'B2': 5.49,
        'C3': 20.00
    }
    return prices.get(product_code, 0)

@app.route('/calculate', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return jsonify({'error': 'No payload provided'}), 400
    
    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity', 1)
        
        if not product_code:
            return jsonify({'error': 'Product code is required'}), 400
        
        unit_price = get_price_for_product_code(product_code)
        total_price = unit_price * quantity
        
        response = yaml.dump({'total_price': total_price})
        return response, 200, {'Content-Type': 'application/yaml'}
    
    except yaml.YAMLError:
        return jsonify({'error': 'Invalid YAML payload'}), 400

if __name__ == '__main__':
    app.run(debug=True)