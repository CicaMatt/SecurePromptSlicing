from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    prices = {
        'A001': 10.0,
        'B002': 15.5,
        'C003': 8.25
    }
    return prices.get(product_code, None)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return Response("Missing query parameter: payload", status=400)
    
    try:
        data = yaml.safe_load(yaml_payload)
    except yaml.YAMLError as exc:
        return Response(f"Error parsing YAML: {exc}", status=400)

    product_code = data.get('product_code')
    quantity = data.get('quantity')

    if not product_code or not isinstance(quantity, int):
        return Response("Invalid payload. Must contain 'product_code' and integer 'quantity'.", status=400)
    
    price_per_item = get_price_for_product_code(product_code)
    if price_per_item is None:
        return Response(f"Product code '{product_code}' not found.", status=404)

    total_price = price_per_item * quantity
    response_payload = {'total_price': total_price}

    return Response(yaml.dump(response_payload), mimetype='application/x-yaml')

if __name__ == '__main__':
    app.run(debug=True)