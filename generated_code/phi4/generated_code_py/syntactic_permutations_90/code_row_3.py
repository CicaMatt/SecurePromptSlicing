from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# In-memory database for simplicity
PRODUCT_PRICES = {
    'product1': 10.0,
    'product2': 20.5,
    'product3': 15.75
}

def get_price_for_product_code(product_code):
    return PRODUCT_PRICES.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return jsonify({'error': 'Missing payload parameter'}), 400

    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity', 1)  # Default to 1 if not provided

        if not product_code or not isinstance(quantity, int):
            return jsonify({'error': 'Invalid payload format'}), 400

        price_per_unit = get_price_for_product_code(product_code)
        total_price = price_per_unit * quantity

        response_payload = yaml.dump({'total_price': total_price})
        return response_payload, 200
    except Exception as e:
        return jsonify({'error': str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)