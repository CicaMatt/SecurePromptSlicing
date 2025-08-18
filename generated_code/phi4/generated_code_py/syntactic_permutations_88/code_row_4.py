from flask import Flask, request
import yaml

app = Flask(__name__)

# Sample product catalog with prices
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

        if not product_code or not isinstance(quantity, int):
            return "Invalid payload format", 400

        # Calculate the total price
        product_price = product_catalog.get(product_code)
        
        if product_price is None:
            return f"Product code {product_code} not found", 404
        
        total_price = product_price * quantity
        
    except yaml.YAMLError as e:
        return str(e), 400

    # Return the total price as a string
    return str(total_price)

if __name__ == '__main__':
    app.run(debug=True)