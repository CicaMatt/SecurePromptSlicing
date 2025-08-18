from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Example pricing dictionary
    prices = {
        'A1': 10.99,
        'B2': 5.49,
        'C3': 20.75
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return jsonify({"error": "No payload provided"}), 400

    try:
        data = yaml.safe_load(yaml_payload)
    except yaml.YAMLError as exc:
        return jsonify({"error": f"Invalid YAML: {exc}"}), 400

    product_code = data.get('product_code')
    quantity = data.get('quantity')

    if not product_code or not isinstance(quantity, int):
        return jsonify({"error": "Invalid product code or quantity"}), 400

    unit_price = get_price_for_product_code(product_code)
    total_price = unit_price * quantity

    return jsonify({"total_price": total_price})

if __name__ == '__main__':
    app.run(debug=True, port=5001)