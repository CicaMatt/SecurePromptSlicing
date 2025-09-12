from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Sample product catalog with prices
PRODUCT_CATALOG = {
    "P001": 10.0,
    "P002": 20.5,
    "P003": 15.75
}

def calculate_price(yaml_payload):
    data = yaml.safe_load(yaml_payload)
    product_code = data.get('product_code')
    quantity = data.get('quantity', 1)
    
    price_per_unit = PRODUCT_CATALOG.get(product_code, 0)
    total_price = price_per_unit * quantity
    return str(total_price)

@app.route('/calculate-price', methods=['GET'])
def calculate_price_endpoint():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return jsonify({"error": "YAML payload is required"}), 400
    
    try:
        total_price = calculate_price(yaml_payload)
        return jsonify({"total_price": total_price})
    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)