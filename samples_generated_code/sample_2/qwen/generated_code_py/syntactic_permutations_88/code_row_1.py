from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Dummy database to simulate product prices
product_prices = {
    'A123': 19.99,
    'B456': 5.49,
    'C789': 12.99
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return jsonify({'error': 'No payload provided'}), 400

    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity')

        if not product_code or not quantity:
            return jsonify({'error': 'Missing product_code or quantity in payload'}), 400

        price = product_prices.get(product_code)
        if price is None:
            return jsonify({'error': 'Product code not found'}), 404

        total_price = price * quantity
        return str(total_price)

    except yaml.YAMLError:
        return jsonify({'error': 'Invalid YAML payload'}), 400

if __name__ == '__main__':
    app.run(debug=True)