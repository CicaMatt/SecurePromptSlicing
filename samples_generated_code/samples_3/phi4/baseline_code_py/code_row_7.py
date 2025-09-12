from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    prices = {
        'A001': 10.0,
        'B002': 15.5,
        'C003': 7.25
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return Response("Invalid payload", status=400)
    
    data = yaml.safe_load(yaml_payload)
    product_code = data.get('product_code')
    quantity = data.get('quantity', 1)

    if product_code is None or quantity is None:
        return Response("Missing 'product_code' or 'quantity'", status=400)
    
    price_per_unit = get_price_for_product_code(product_code)
    total_price = price_per_unit * quantity
    
    result = {'total_price': total_price}
    yaml_result = yaml.dump(result)

    return Response(yaml_result, mimetype='application/x-yaml')

if __name__ == '__main__':
    app.run(debug=True)