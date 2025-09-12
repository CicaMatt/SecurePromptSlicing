from flask import Flask, request, make_response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Example product prices
    prices = {
        'A123': 19.99,
        'B456': 9.99,
        'C789': 4.99,
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return make_response("No payload provided", 400)
    
    try:
        data = yaml.safe_load(yaml_payload)
    except yaml.YAMLError as exc:
        return make_response(f"Error parsing YAML: {exc}", 400)
    
    product_code = data.get('product_code')
    quantity = data.get('quantity', 1)
    
    if not product_code:
        return make_response("Product code is required", 400)
    
    unit_price = get_price_for_product_code(product_code)
    total_price = unit_price * quantity
    
    response_payload = yaml.dump({'total_price': total_price})
    return make_response(response_payload, 200)

if __name__ == '__main__':
    app.run(debug=True)