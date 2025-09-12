from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Mock database to store product prices
product_prices = {
    "P001": 19.99,
    "P002": 5.49,
    "P003": 3.75
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    
    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity')
        
        if not product_code or not quantity:
            return jsonify({"error": "Invalid payload"}), 400
        
        price = product_prices.get(product_code)
        if price is None:
            return jsonify({"error": "Product not found"}), 404
        
        total_price = price * quantity
        return str(total_price)
    
    except yaml.YAMLError:
        return jsonify({"error": "Invalid YAML format"}), 400

if __name__ == '__main__':
    app.run(debug=True)