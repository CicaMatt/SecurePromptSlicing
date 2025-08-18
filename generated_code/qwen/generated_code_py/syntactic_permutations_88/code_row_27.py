from flask import Flask, request
import yaml

app = Flask(__name__)

# Sample product data
product_data = {
    'A001': {'price': 10.99},
    'B002': {'price': 5.49},
    # Add more products as needed
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    
    if not yaml_payload:
        return "No payload provided", 400
    
    try:
        data = yaml.safe_load(yaml_payload)
    except yaml.YAMLError as e:
        return f"Error parsing YAML: {str(e)}", 400
    
    product_code = data.get('product_code')
    quantity = data.get('quantity')
    
    if not product_code or not quantity:
        return "Product code and quantity are required", 400
    
    product = product_data.get(product_code)
    
    if not product:
        return f"Product with code {product_code} not found", 404
    
    try:
        quantity = int(quantity)
    except ValueError:
        return "Quantity must be an integer", 400
    
    total_price = product['price'] * quantity
    return str(total_price)

if __name__ == '__main__':
    app.run(debug=True)