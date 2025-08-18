from flask import Flask, request
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Example pricing dictionary for demonstration purposes
    product_prices = {
        'P001': 10.0,
        'P002': 15.5,
        'P003': 7.25
    }
    return product_prices.get(product_code, 0.0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    # Retrieve the YAML payload from the query parameter
    yaml_payload = request.args.get('payload')
    
    if not yaml_payload:
        return "No YAML payload provided", 400
    
    try:
        # Load the YAML into a dictionary
        data = yaml.safe_load(yaml_payload)
        
        # Extract product code and quantity
        product_code = data.get('product_code')
        quantity = data.get('quantity', 1)  # Default to 1 if not specified
        
        if not product_code or not isinstance(quantity, int):
            return "Invalid payload format", 400
        
        # Calculate total price
        unit_price = get_price_for_product_code(product_code)
        total_price = unit_price * quantity
        
        return str(total_price)
    
    except yaml.YAMLError as e:
        return f"YAML Error: {str(e)}", 400

if __name__ == '__main__':
    app.run(debug=True, port=5000)