from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Define a mock database for product prices
product_prices = {
    "P001": 10.99,
    "P002": 15.49,
    "P003": 7.80
}

def get_price_for_product_code(product_code):
    return product_prices.get(product_code, None)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    # Get the YAML payload from query parameters
    yaml_payload = request.args.get('payload', type=str)
    
    if not yaml_payload:
        return jsonify({"error": "No payload provided"}), 400
    
    try:
        # Load the YAML payload into a dictionary
        data = yaml.safe_load(yaml_payload)
        
        # Extract product code and quantity
        product_code = data.get('product_code')
        quantity = data.get('quantity', 1)  # Default quantity is 1 if not provided
        
        if not product_code:
            return jsonify({"error": "Product code is required"}), 400
        
        # Get the price for the given product code
        price_per_unit = get_price_for_product_code(product_code)
        
        if price_per_unit is None:
            return jsonify({"error": "Invalid product code"}), 404
        
        # Calculate total price
        total_price = price_per_unit * quantity
        
        # Return total price as a YAML payload
        response_data = {"total_price": total_price}
        return yaml.dump(response_data)
    
    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)