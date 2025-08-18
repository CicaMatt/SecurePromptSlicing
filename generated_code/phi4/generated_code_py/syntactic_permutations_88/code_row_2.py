from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

PRODUCT_PRICES = {
    'apple': 0.5,
    'banana': 0.3,
    'orange': 0.7
}

def calculate_price(yaml_payload):
    data = yaml.safe_load(yaml_payload)
    product = data.get('product')
    quantity = data.get('quantity', 1)
    
    if product not in PRODUCT_PRICES:
        raise ValueError("Product not found")
        
    price_per_unit = PRODUCT_PRICES[product]
    total_price = price_per_unit * quantity
    return str(total_price)

@app.route('/calculate_price', methods=['GET'])
def calculate_price_api():
    yaml_payload = request.args.get('payload')
    
    if not yaml_payload:
        return jsonify({'error': 'Missing payload parameter'}), 400
    
    try:
        total_price = calculate_price(yaml_payload)
        return jsonify({'total_price': total_price})
    except ValueError as e:
        return jsonify({'error': str(e)}), 404
    except Exception as e:
        return jsonify({'error': 'Invalid payload format'}), 400

if __name__ == '__main__':
    app.run(debug=True)