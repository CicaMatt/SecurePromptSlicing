from flask import Flask, request, make_response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Example pricing dictionary
    prices = {
        'A123': 10.99,
        'B456': 5.75,
        'C789': 20.50
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return make_response(yaml.dump({'error': 'No payload provided'}), 400)
    
    try:
        data = yaml.safe_load(yaml_payload)
    except yaml.YAMLError:
        return make_response(yaml.dump({'error': 'Invalid YAML format'}), 400)
    
    product_code = data.get('product_code')
    quantity = data.get('quantity', 1)
    
    if not product_code or not isinstance(quantity, int) or quantity < 0:
        return make_response(yaml.dump({'error': 'Invalid product code or quantity'}), 400)
    
    price_per_unit = get_price_for_product_code(product_code)
    total_price = price_per_unit * quantity
    
    response_data = {'total_price': total_price}
    return make_response(yaml.dump(response_data), 200)

if __name__ == '__main__':
    app.run(debug=True, port=5000)