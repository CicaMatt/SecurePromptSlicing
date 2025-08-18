from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def get_price_for_product_code():
    # Example product prices
    product_prices = {
        'A1': 10.0,
        'B2': 15.5,
        'C3': 20.0
    }
    
    query_param = request.args.get('payload')
    if not query_param:
        return Response("Missing payload", status=400)
    
    try:
        data = yaml.safe_load(query_param)
    except yaml.YAMLError:
        return Response("Invalid YAML", status=400)

    product_code = data.get('product_code')
    quantity = data.get('quantity')

    if not product_code or not isinstance(quantity, (int, float)):
        return Response("Invalid product code or quantity", status=400)
    
    price_per_unit = product_prices.get(product_code)
    if price_per_unit is None:
        return Response(f"Product code {product_code} not found", status=404)

    total_price = price_per_unit * quantity
    response_data = {'total_price': total_price}
    
    yaml_response = yaml.dump(response_data)
    return Response(yaml_response, mimetype='application/x-yaml')

@app.route('/get-price', methods=['GET'])
def api_get_price():
    return get_price_for_product_code()

if __name__ == '__main__':
    app.run(debug=True, port=5000)