from flask import Flask, request, make_response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # This is a mock function to simulate fetching the price for a product code
    prices = {
        'A123': 10.99,
        'B456': 15.75,
        'C789': 7.49
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
    
    if not product_code:
        return make_response(yaml.dump({'error': 'Product code is required'}), 400)
    
    price_per_unit = get_price_for_product_code(product_code)
    total_price = price_per_unit * quantity
    
    response_data = {
        'product_code': product_code,
        'quantity': quantity,
        'total_price': total_price
    }
    
    return make_response(yaml.dump(response_data), 200)

if __name__ == '__main__':
    app.run(debug=True)