from flask import Flask, request
import yaml

app = Flask(__name__)

# Example product catalog with prices
product_catalog = {
    'P001': 10.0,
    'P002': 20.5,
    'P003': 15.75
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    # Extract YAML payload from query parameter
    yaml_payload = request.args.get('payload')
    
    if not yaml_payload:
        return "No payload provided", 400

    try:
        # Parse the YAML payload
        data = yaml.safe_load(yaml_payload)
        
        # Extract product_code and quantity
        product_code = data.get('product_code')
        quantity = data.get('quantity')

        if not product_code or not quantity:
            return "Invalid payload", 400

        # Get product price from catalog
        product_price = product_catalog.get(product_code)

        if product_price is None:
            return f"Product code {product_code} not found", 404
        
        # Calculate total price
        total_price = product_price * quantity

        # Return the total price as a string
        return str(total_price)
    
    except yaml.YAMLError:
        return "Error parsing YAML payload", 400

if __name__ == '__main__':
    app.run(debug=True)