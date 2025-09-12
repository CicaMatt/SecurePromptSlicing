from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Simple hardcoded prices for demonstration purposes
    product_prices = {
        "A": 10,
        "B": 20,
        "C": 30
    }
    return product_prices.get(product_code, 0)

@app.route('/calculate_price')
def calculate_price():
    yaml_payload = request.args.get('payload', '')
    if not yaml_payload:
        return Response("No payload provided", status=400)
    
    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity')

        if product_code is None or quantity is None:
            return Response("Invalid payload format", status=400)

        price_per_item = get_price_for_product_code(product_code)
        total_price = price_per_item * quantity

        result = {'total_price': total_price}
        response_payload = yaml.dump(result)

        return Response(response_payload, mimetype='application/x-yaml')
    
    except yaml.YAMLError:
        return Response("Invalid YAML format", status=400)

if __name__ == '__main__':
    app.run(debug=True)