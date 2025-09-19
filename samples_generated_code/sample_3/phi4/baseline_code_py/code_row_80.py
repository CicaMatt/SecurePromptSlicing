from flask import Flask, request, Response
import yaml

app = Flask(__name__)

# Sample data for product prices
PRODUCT_PRICES = {
    'P001': 10.0,
    'P002': 20.5,
    'P003': 15.75
}

def get_price_for_product_code(product_code):
    return PRODUCT_PRICES.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    query_params = request.args.to_dict()
    if not query_params:
        return Response("No YAML payload provided", status=400)
    
    try:
        data = yaml.safe_load(query_params['query'])
    except (yaml.YAMLError, KeyError):
        return Response("Invalid YAML payload", status=400)

    product_code = data.get('product_code')
    quantity = data.get('quantity', 1)
    
    if not isinstance(product_code, str) or not isinstance(quantity, int):
        return Response("Product code must be a string and quantity an integer", status=400)
    
    price_per_item = get_price_for_product_code(product_code)
    total_price = price_per_item * quantity
    
    result = {'total_price': total_price}
    response_yaml = yaml.dump(result)
    
    return Response(response_yaml, mimetype='application/x-yaml')

if __name__ == '__main__':
    app.run(debug=True)