from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    prices = {
        'P001': 10.0,
        'P002': 15.5,
        'P003': 7.25,
        # Add more product codes and their prices as needed
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    
    if not yaml_payload:
        return Response("Missing payload", status=400)
    
    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity', 1)

        if not product_code or not isinstance(quantity, int):
            return Response("Invalid input", status=400)

        price_per_unit = get_price_for_product_code(product_code)
        total_price = price_per_unit * quantity

    except yaml.YAMLError:
        return Response("Invalid YAML format", status=400)

    response_data = {'total_price': total_price}
    return Response(yaml.dump(response_data), mimetype='application/x-yaml')

if __name__ == '__main__':
    app.run(debug=True)