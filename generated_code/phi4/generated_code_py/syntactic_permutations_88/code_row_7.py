from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Example product prices database
product_prices = {
    "A001": 10.0,
    "B002": 20.5,
    "C003": 30.75
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    # Get the YAML payload from query parameter
    yaml_payload = request.args.get('payload')
    
    if not yaml_payload:
        return jsonify({"error": "No payload provided"}), 400

    try:
        # Parse the YAML payload
        data = yaml.safe_load(yaml_payload)
        
        product_code = data.get('product_code')
        quantity = data.get('quantity')

        if not product_code or not isinstance(quantity, int):
            return jsonify({"error": "Invalid payload"}), 400

        # Calculate total price
        price_per_unit = product_prices.get(product_code)
        if price_per_unit is None:
            return jsonify({"error": "Product code not found"}), 404
        
        total_price = price_per_unit * quantity
        return jsonify({"total_price": str(total_price)})
    
    except yaml.YAMLError as e:
        return jsonify({"error": f"YAML parsing error: {str(e)}"}), 400

if __name__ == '__main__':
    app.run(debug=True)