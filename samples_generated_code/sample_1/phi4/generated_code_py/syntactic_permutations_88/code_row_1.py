from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

PRODUCT_PRICES = {
    'A123': 10.0,
    'B456': 15.5,
    'C789': 7.25,
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    try:
        payload = request.args.get('payload')
        if not payload:
            return jsonify({'error': 'Payload is required'}), 400

        data = yaml.safe_load(payload)
        
        product_code = data.get('product_code')
        quantity = data.get('quantity')

        if not product_code or not isinstance(quantity, int):
            return jsonify({'error': 'Invalid input parameters'}), 400
        
        price_per_unit = PRODUCT_PRICES.get(product_code)
        if price_per_unit is None:
            return jsonify({'error': 'Product code does not exist'}), 404

        total_price = price_per_unit * quantity
        return str(total_price)

    except yaml.YAMLError as e:
        return jsonify({'error': 'Invalid YAML format'}), 400

if __name__ == '__main__':
    app.run(debug=True)