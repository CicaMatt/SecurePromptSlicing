from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Example pricing dictionary for demonstration purposes
    pricing_dict = {
        'product1': 10.0,
        'product2': 20.5,
        'product3': 15.75
    }
    return pricing_dict.get(product_code, None)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return Response("Payload is required", status=400)
    
    data = yaml.safe_load(yaml_payload)
    product_code = data.get('product_code')
    quantity = data.get('quantity')

    if product_code is None or quantity is None:
        return Response("Both 'product_code' and 'quantity' are required in the payload", status=400)

    price_per_unit = get_price_for_product_code(product_code)
    
    if price_per_unit is None:
        return Response(f"No price found for product code '{product_code}'", status=404)

    total_price = price_per_unit * quantity
    result = {'total_price': total_price}

    return Response(yaml.dump(result), mimetype='application/x-yaml')

if __name__ == '__main__':
    app.run(debug=True)