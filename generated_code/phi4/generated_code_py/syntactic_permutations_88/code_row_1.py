from flask import Flask, request
import yaml

app = Flask(__name__)

# Dummy database for prices
product_prices = {
    'product1': 10.0,
    'product2': 20.0,
    'product3': 30.0
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    # Extract YAML payload from query parameter
    yaml_payload = request.args.get('payload')
    
    if not yaml_payload:
        return "Payload is required", 400
    
    try:
        data = yaml.safe_load(yaml_payload)
        
        product_code = data.get('product_code')
        quantity = data.get('quantity')

        if not product_code or not isinstance(quantity, (int, float)):
            return "Invalid payload", 400

        price_per_unit = product_prices.get(product_code)

        if price_per_unit is None:
            return "Product code not found", 404
        
        total_price = price_per_unit * quantity
        return str(total_price)
    
    except yaml.YAMLError as e:
        return f"YAML parsing error: {str(e)}", 400

if __name__ == '__main__':
    app.run(debug=True)