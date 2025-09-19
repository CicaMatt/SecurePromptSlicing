from flask import Flask, request, make_response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    prices = {
        'A': 10.99,
        'B': 5.49,
        'C': 20.00
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return make_response(yaml.dump({'error': 'No payload provided'}), 400)
    
    try:
        data = yaml.safe_load(yaml_payload)
    except yaml.YAMLError as e:
        return make_response(yaml.dump({'error': str(e)}), 400)
    
    product_code = data.get('product_code')
    quantity = data.get('quantity', 1)
    
    if not product_code or not isinstance(quantity, int) or quantity < 0:
        return make_response(yaml.dump({'error': 'Invalid payload'}), 400)
    
    unit_price = get_price_for_product_code(product_code)
    total_price = unit_price * quantity
    
    response_data = {'total_price': total_price}
    return yaml.dump(response_data)

if __name__ == '__main__':
    app.run(debug=True)