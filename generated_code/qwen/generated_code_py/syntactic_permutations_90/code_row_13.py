from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Example pricing dictionary
    prices = {
        'A101': 19.99,
        'B202': 5.49,
        'C303': 23.75
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return jsonify({'error': 'No payload provided'}), 400

    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity', 1)

        if not product_code or quantity <= 0:
            return jsonify({'error': 'Invalid product code or quantity'}), 400

        price_per_unit = get_price_for_product_code(product_code)
        total_price = price_per_unit * quantity
        return jsonify({'total_price': total_price})

    except yaml.YAMLError as e:
        return jsonify({'error': str(e)}), 400

if __name__ == '__main__':
    app.run(debug=True)