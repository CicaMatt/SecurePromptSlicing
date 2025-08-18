from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # This is a placeholder for actual product pricing logic
    price_map = {
        'A1': 10.99,
        'B2': 5.49,
        'C3': 20.00
    }
    return price_map.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return jsonify({'error': 'No payload provided'}), 400

    try:
        data = yaml.safe_load(yaml_payload)
    except yaml.YAMLError as e:
        return jsonify({'error': f'Invalid YAML: {str(e)}'}), 400

    product_code = data.get('product_code')
    quantity = data.get('quantity')

    if not product_code or not isinstance(quantity, int) or quantity < 1:
        return jsonify({'error': 'Invalid product code or quantity'}), 400

    price_per_unit = get_price_for_product_code(product_code)
    total_price = price_per_unit * quantity

    response_yaml = yaml.dump({'total_price': total_price})
    return response_yaml, 200, {'Content-Type': 'application/yaml'}

if __name__ == '__main__':
    app.run(debug=True)