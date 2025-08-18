from flask import Flask, request
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Example product prices
    product_prices = {
        'A': 10,
        'B': 20,
        'C': 30
    }
    return product_prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    
    if not yaml_payload:
        return "Error: No payload provided", 400

    try:
        data = yaml.safe_load(yaml_payload)
    except yaml.YAMLError as e:
        return f"Error loading YAML: {e}", 400
    
    product_code = data.get('product_code')
    quantity = data.get('quantity', 1)

    if not product_code or not isinstance(quantity, int):
        return "Error: Invalid payload", 400

    price_per_product = get_price_for_product_code(product_code)
    total_price = price_per_product * quantity
    result = {'total_price': total_price}

    return yaml.dump(result), 200

if __name__ == '__main__':
    app.run(debug=True)