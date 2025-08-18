from flask import Flask, request
import yaml

app = Flask(__name__)

# Sample product database
PRODUCTS = {
    'A001': 10.0,
    'B002': 20.5,
    'C003': 15.75
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    # Get YAML payload from query parameter
    yaml_payload = request.args.get('payload')
    
    if not yaml_payload:
        return "Missing payload", 400
    
    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity')

        if not product_code or not isinstance(quantity, int):
            return "Invalid payload format", 400

        # Calculate total price
        price_per_unit = PRODUCTS.get(product_code)
        
        if price_per_unit is None:
            return f"Product code {product_code} not found", 404
        
        total_price = price_per_unit * quantity
        return str(total_price)

    except yaml.YAMLError as e:
        return "Error parsing YAML payload", 400

if __name__ == '__main__':
    app.run(debug=True)