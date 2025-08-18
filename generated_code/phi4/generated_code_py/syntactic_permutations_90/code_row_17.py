from flask import Flask, request, Response
import yaml

app = Flask(__name__)

# Mock database for product prices
PRODUCT_PRICES = {
    'P001': 10.0,
    'P002': 20.5,
    'P003': 15.75
}

def get_price_for_product_code(product_code):
    return PRODUCT_PRICES.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    payload = request.args.get('payload')
    
    if not payload:
        return Response(status=400)
    
    try:
        data = yaml.safe_load(payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity')

        if not product_code or not isinstance(quantity, int):
            return Response(status=400)

        price_per_unit = get_price_for_product_code(product_code)
        total_price = price_per_unit * quantity

    except Exception as e:
        return Response(status=500)
    
    response_data = {'total_price': total_price}
    return Response(yaml.dump(response_data), mimetype='application/x-yaml')

if __name__ == '__main__':
    app.run(debug=True)