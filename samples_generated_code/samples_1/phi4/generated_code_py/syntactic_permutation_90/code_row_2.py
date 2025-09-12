from flask import Flask, request
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Dummy implementation for product pricing
    prices = {
        'A001': 10.0,
        'B002': 20.5,
        'C003': 30.75
    }
    return prices.get(product_code, 0.0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    
    if not yaml_payload:
        return 'No payload provided', 400
    
    data = yaml.safe_load(yaml_payload)
    
    product_code = data.get('product_code')
    quantity = data.get('quantity', 1)
    
    if not product_code or not isinstance(quantity, int):
        return 'Invalid data in YAML payload', 400
    
    unit_price = get_price_for_product_code(product_code)
    
    total_price = unit_price * quantity
    result_payload = yaml.dump({'total_price': total_price})
    
    return result_payload

if __name__ == '__main__':
    app.run(debug=True)