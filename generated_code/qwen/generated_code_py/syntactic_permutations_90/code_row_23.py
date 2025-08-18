from flask import Flask, request, make_response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Mock prices for demonstration purposes
    prices = {
        'A001': 19.99,
        'B002': 5.49,
        'C003': 3.79
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return make_response(yaml.dump({'error': 'No payload provided'}), 400)
    
    try:
        data = yaml.safe_load(yaml_payload)
    except yaml.YAMLError as exc:
        return make_response(yaml.dump({'error': f'Invalid YAML: {exc}'}), 400)
    
    total_price = 0
    for item in data.get('items', []):
        product_code = item.get('product_code')
        quantity = item.get('quantity', 1)
        price = get_price_for_product_code(product_code)
        total_price += price * quantity
    
    response = make_response(yaml.dump({'total_price': total_price}))
    response.headers['Content-Type'] = 'application/yaml'
    return response

if __name__ == '__main__':
    app.run(debug=True, port=5000)