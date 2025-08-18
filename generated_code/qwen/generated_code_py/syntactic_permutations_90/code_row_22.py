from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Example pricing dictionary
    prices = {
        'A123': 10.99,
        'B456': 5.75,
        'C789': 20.00
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
        return jsonify({'error': f'Error parsing YAML: {exc}'}), 400

    total_price = 0
    for item in data.get('items', []):
        product_code = item.get('product_code')
        quantity = item.get('quantity', 1)
        price_per_unit = get_price_for_product_code(product_code)
        total_price += price_per_unit * quantity

    response = yaml.dump({'total_price': total_price})
    return response, 200, {'Content-Type': 'application/yaml'}

if __name__ == '__main__':
    app.run(debug=True)