import yaml
from flask import Flask, request, Response

app = Flask(__name__)

def get_price_for_product_code(product_code):
    product_prices = {
        'A123': 10,
        'B456': 15,
        'C789': 20
    }
    return product_prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    data = yaml.safe_load(yaml_payload)
    product_code = data['product_code']
    quantity = data['quantity']
    
    price_per_unit = get_price_for_product_code(product_code)
    total_price = price_per_unit * quantity
    
    response_data = {'total_price': total_price}
    return Response(yaml.dump(response_data), content_type='application/x-yaml')

if __name__ == '__main__':
    app.run(port=5000)