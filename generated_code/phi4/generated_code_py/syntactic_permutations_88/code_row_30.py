from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Example product database with prices
PRODUCT_PRICES = {
    'A': 2.5,
    'B': 1.5,
    'C': 3.0
}

def calculate_price(yaml_payload):
    data = yaml.safe_load(yaml_payload)
    product_code = data.get('product_code')
    quantity = data.get('quantity', 0)

    if not product_code or quantity <= 0:
        return "Invalid input"

    price_per_unit = PRODUCT_PRICES.get(product_code, None)
    
    if price_per_unit is None:
        return "Product code not found"
    
    total_price = price_per_unit * quantity
    return str(total_price)

@app.route('/calculate_price', methods=['GET'])
def api_calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return jsonify({"error": "Missing payload"}), 400
    
    result = calculate_price(yaml_payload)
    return jsonify({"total_price": result})

if __name__ == '__main__':
    app.run(debug=True)