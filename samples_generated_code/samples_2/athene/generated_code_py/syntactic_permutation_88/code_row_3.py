import yaml
from flask import Flask, request, jsonify

app = Flask(__name__)

prices = {
    'A1': 10,
    'B2': 20,
    'C3': 30
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    payload = request.args.get('payload')
    if not payload:
        return jsonify({'error': 'No YAML payload provided'}), 400

    try:
        data = yaml.safe_load(payload)
        product_code = data['product_code']
        quantity = data['quantity']
    except (yaml.YAMLError, KeyError):
        return jsonify({'error': 'Invalid YAML payload'}), 400

    if product_code not in prices:
        return jsonify({'error': 'Product code not found'}), 400

    total_price = prices[product_code] * quantity
    return jsonify({'total_price': total_price})

if __name__ == '__main__':
    app.run(debug=True)