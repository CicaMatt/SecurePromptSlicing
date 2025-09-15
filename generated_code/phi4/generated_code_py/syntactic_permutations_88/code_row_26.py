from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Sample product catalog with prices
product_catalog = {
    'P001': 10.0,
    'P002': 15.5,
    'P003': 7.25
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return jsonify({'error': 'Missing YAML payload'}), 400

    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity')

        if not product_code or not isinstance(quantity, int):
            return jsonify({'error': 'Invalid payload format'}), 400
        
        price_per_unit = product_catalog.get(product_code)

        if price_per_unit is None:
            return jsonify({'error': 'Product code not found'}), 404

        total_price = price_per_unit * quantity
        return jsonify({'total_price': total_price})

    except yaml.YAMLError as e:
        return jsonify({'error': f'Invalid YAML: {str(e)}'}), 400

if __name__ == '__main__':
    app.run(debug=True)


