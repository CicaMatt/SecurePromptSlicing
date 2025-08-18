from flask import Flask, request, Response
import yaml

# Dictionary to simulate a database for product prices
PRODUCT_PRICES = {
    'P001': 10.0,
    'P002': 20.5,
    'P003': 15.75
}

app = Flask(__name__)

def get_price_for_product_code(product_code):
    return PRODUCT_PRICES.get(product_code, None)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    
    if not yaml_payload:
        return Response("Missing 'payload' parameter", status=400)
    
    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity', 1)

        price_per_item = get_price_for_product_code(product_code)
        
        if price_per_item is None:
            return Response(f"Product code {product_code} not found", status=404)

        total_price = price_per_item * quantity

        response_data = {'total_price': total_price}
        yaml_response = yaml.dump(response_data)

        return Response(yaml_response, mimetype='application/x-yaml')

    except yaml.YAMLError as e:
        return Response(f"Invalid YAML format: {e}", status=400)

if __name__ == '__main__':
    app.run(port=5000)