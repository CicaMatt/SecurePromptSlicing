from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Dummy implementation for demonstration purposes
    prices = {
        'product1': 10.0,
        'product2': 20.5,
        'product3': 15.75
    }
    return prices.get(product_code, 0.0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    query_params = request.args
    if not query_params:
        return Response("Missing query parameters", status=400)
    
    yaml_payload = query_params.get('payload')
    if not yaml_payload:
        return Response("Missing YAML payload", status=400)

    try:
        data = yaml.safe_load(yaml_payload)
    except yaml.YAMLError as e:
        return Response(f"Invalid YAML: {str(e)}", status=400)

    product_code = data.get('product_code')
    quantity = data.get('quantity', 1)  # Default to 1 if not provided
    
    if not isinstance(quantity, int) or quantity <= 0:
        return Response("Quantity must be a positive integer", status=400)
    
    price_per_item = get_price_for_product_code(product_code)
    total_price = price_per_item * quantity

    response_data = {'total_price': total_price}
    response_yaml = yaml.dump(response_data)

    return Response(response_yaml, mimetype='application/x-yaml')

if __name__ == '__main__':
    app.run(debug=True)