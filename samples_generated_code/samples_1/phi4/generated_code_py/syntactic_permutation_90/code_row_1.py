from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Example product data; in a real application, this might be queried from a database.
    products = {
        'A001': 10.0,
        'B002': 15.5,
        'C003': 7.75
    }
    return products.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return jsonify({'error': 'No payload provided'}), 400

    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity', 1)

        if not product_code or not isinstance(quantity, int):
            return jsonify({'error': 'Invalid payload format'}), 400

        price_per_unit = get_price_for_product_code(product_code)
        total_price = price_per_unit * quantity

        result = yaml.dump({'total_price': total_price})
        return result, 200
    except Exception as e:
        return jsonify({'error': str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)