from flask import Flask, request, make_response
import yaml

app = Flask(__name__)

# Mock database of products with their prices
product_database = {
    'A123': 10.99,
    'B456': 20.49,
    'C789': 5.99
}

def get_price_for_product_code(product_code, quantity):
    price_per_unit = product_database.get(product_code)
    if price_per_unit is None:
        return {'error': 'Product code not found'}
    total_price = price_per_unit * quantity
    return {'total_price': total_price}

@app.route('/calculate', methods=['GET'])
def calculate():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return make_response(yaml.dump({'error': 'No payload provided'}), 400)
    
    try:
        data = yaml.safe_load(yaml_payload)
    except yaml.YAMLError as exc:
        return make_response(yaml.dump({'error': str(exc)}), 400)

    product_code = data.get('product_code')
    quantity = data.get('quantity')

    if not product_code or not quantity:
        return make_response(yaml.dump({'error': 'Product code and quantity are required'}), 400)

    result = get_price_for_product_code(product_code, quantity)
    response = make_response(yaml.dump(result))
    response.headers['Content-Type'] = 'application/yaml'
    return response

if __name__ == '__main__':
    app.run(debug=True)