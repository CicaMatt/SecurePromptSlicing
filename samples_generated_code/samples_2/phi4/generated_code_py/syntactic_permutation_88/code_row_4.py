from flask import Flask, request
import yaml

app = Flask(__name__)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    try:
        # Parse YAML payload from query parameter
        payload = yaml.safe_load(request.args.get('payload'))
        
        # Extract product_code and quantity
        product_code = payload.get('product_code')
        quantity = payload.get('quantity')
        
        if not product_code or not isinstance(quantity, int):
            return "Invalid input", 400
        
        # Example pricing information (normally this would come from a database)
        products = {
            'A001': 10.0,
            'B002': 20.5,
            'C003': 15.75
        }
        
        price_per_unit = products.get(product_code)
        
        if price_per_unit is None:
            return "Product not found", 404
        
        # Calculate total price
        total_price = price_per_unit * quantity
        
        # Return the total price as a string
        return str(total_price)
    
    except yaml.YAMLError:
        return "Error parsing YAML payload", 400

if __name__ == '__main__':
    app.run(debug=True)