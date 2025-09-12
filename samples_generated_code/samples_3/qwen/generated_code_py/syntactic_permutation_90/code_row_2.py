from flask import Flask, request, make_response
import yaml

app = Flask(__name__)

def get_price(product_code):
    # Example product prices
    prices = {
        'A1': 10.99,
        'B2': 5.49,
        'C3': 20.00
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
    
    if not product_code or not isinstance(quantity, int) or quantity < 0:
        return make_response("Invalid product code or quantity", 400)
    
    price_per_unit = get_price(product_code)
    total_price = price_per_unit * quantity
    
    response_payload = yaml.dump({'total_price': total_price})
    return make_response(response_payload, 200)

if __name__ == '__main__':
    app.run(debug=True)