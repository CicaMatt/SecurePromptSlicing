from flask import Flask, request, make_response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Example pricing dictionary
    prices = {
        'A123': 10.99,
        'B456': 15.75,
        'C789': 20.50
    }
    return prices.get(product_code, 0.0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return make_response("No payload provided", 400)
    
    try:
        data = yaml.safe_load(yaml_payload)
    except yaml.YAMLError as e:
        return make_response(f"Error parsing YAML: {str(e)}", 400)
    
    total_price = 0.0
    for item in data.get('items', []):
        product_code = item.get('product_code')
        quantity = item.get('quantity', 1)
        price = get_price_for_product_code(product_code)
        total_price += price * quantity
    
    response_payload = yaml.dump({'total_price': total_price})
    return make_response(response_payload, 200)

if __name__ == '__main__':
    app.run(debug=True)