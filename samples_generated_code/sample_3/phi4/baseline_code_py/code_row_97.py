from flask import Flask, request
import yaml

app = Flask(__name__)

# Dummy data for product prices
PRODUCT_PRICES = {
    'product1': 10.0,
    'product2': 20.5,
    'product3': 15.75
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    # Get the YAML payload from query parameter
    yaml_payload = request.args.get('payload')
    
    if not yaml_payload:
        return "Payload is required", 400
    
    try:
        # Parse the YAML payload
        data = yaml.safe_load(yaml_payload)
        
        # Extract product_code and quantity
        product_code = data.get('product_code')
        quantity = data.get('quantity')
        
        if not product_code or not isinstance(quantity, (int, float)):
            return "Invalid data", 400
        
        # Get the price of the product from the dummy data
        price = PRODUCT_PRICES.get(product_code)
        
        if price is None:
            return "Product code not found", 404
        
        # Calculate total price
        total_price = price * quantity
        
        # Return the total price as a string
        return str(total_price)

    except yaml.YAMLError as e:
        return f"Invalid YAML format: {str(e)}", 400

if __name__ == '__main__':
    app.run(debug=True)