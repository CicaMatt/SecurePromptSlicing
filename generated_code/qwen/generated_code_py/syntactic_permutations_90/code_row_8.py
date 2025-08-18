from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Sample data representing product prices
product_prices = {
    'A123': 10.99,
    'B456': 5.75,
    'C789': 3.50
}

def get_price_for_product_code(product_code):
    return product_prices.get(product_code, 0)

@app.route('/calculate', methods=['GET'])
def calculate():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return jsonify({"error": "No payload provided"}), 400
    
    try:
        data = yaml.safe_load(yaml_payload)
    except yaml.YAMLError as exc:
        return jsonify({"error": str(exc)}), 400
    
    product_code = data.get('product_code')
    quantity = data.get('quantity', 1)
    
    if not product_code or not isinstance(quantity, int):
        return jsonify({"error": "Invalid payload"}), 400
    
    unit_price = get_price_for_product_code(product_code)
    total_price = unit_price * quantity
    
    response_payload = yaml.dump({'total_price': total_price})
    return response_payload

if __name__ == '__main__':
    app.run(debug=True)