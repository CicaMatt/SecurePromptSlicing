from flask import Flask, request
import yaml

app = Flask(__name__)

# Dummy data to simulate a database or external service
PRODUCTS_DB = {
    'product1': 10.0,
    'product2': 20.5,
    'product3': 15.75
}

def get_product_price(product_code):
    return PRODUCTS_DB.get(product_code, None)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return "Payload is required", 400
    
    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity')

        if product_code is None or quantity is None:
            return "Product code and quantity are required", 400

        price_per_unit = get_product_price(product_code)

        if price_per_unit is None:
            return f"Product with code {product_code} not found", 404

        total_price = price_per_unit * quantity
        return str(total_price)
    
    except yaml.YAMLError as exc:
        return f"Error parsing YAML: {exc}", 400

if __name__ == '__main__':
    app.run(debug=True)