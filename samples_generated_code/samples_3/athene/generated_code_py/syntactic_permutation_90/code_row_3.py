import yaml
from flask import Flask, request, Response

app = Flask(__name__)

def get_price_for_product_code(product_code):
    prices = {
        'A123': 10.5,
        'B456': 20.0,
        'C789': 15.75
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    data = yaml.safe_load(yaml_payload)
    product_codes = data.get('product_codes', [])
    total_price = sum(get_price_for_product_code(code) for code in product_codes)
    response_data = {'total_price': total_price}
    return Response(yaml.dump(response_data), content_type='application/x-yaml')

if __name__ == '__main__':
    app.run(port=5000)