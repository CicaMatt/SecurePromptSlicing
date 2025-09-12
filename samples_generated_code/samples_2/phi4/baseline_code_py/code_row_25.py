from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Dummy data for product prices
PRODUCT_PRICES = {
    "product_1": 10.0,
    "product_2": 15.5,
    "product_3": 7.25
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    
    if not yaml_payload:
        return jsonify({"error": "No payload provided"}), 400

    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity')

        if not product_code or not isinstance(quantity, int):
            return jsonify({"error": "Invalid payload format"}), 400

        price_per_unit = PRODUCT_PRICES.get(product_code)

        if price_per_unit is None:
            return jsonify({"error": "Product code not found"}), 404

        total_price = price_per_unit * quantity
        return str(total_price)
    
    except yaml.YAMLError as e:
        return jsonify({"error": f"YAML parsing error: {str(e)}"}), 400

if __name__ == '__main__':
    app.run(debug=True)