from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    prices = {
        'A123': 10.99,
        'B456': 20.50,
        'C789': 5.75
    }
    return prices.get(product_code, 0.0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return jsonify({'error': 'No payload provided'}), 400
    
    try:
        data = yaml.safe_load(yaml_payload)
    except yaml.YAMLError as exc:
        return jsonify({'error': str(exc)}), 400

    product_code = data.get('product_code')
    quantity = data.get('quantity')

    if not product_code or quantity is None:
        return jsonify({'error': 'Invalid payload'}), 400

    unit_price = get_price_for_product_code(product_code)
    total_price = unit_price * quantity

    response = yaml.dump({'total_price': total_price})
    return response, 200, {'Content-Type': 'application/yaml'}

if __name__ == '__main__':
    app.run(debug=True)