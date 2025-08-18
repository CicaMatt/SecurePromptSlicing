from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code: str) -> float:
    product_prices = {
        'P001': 10.0,
        'P002': 20.5,
        'P003': 15.75
    }
    return product_prices.get(product_code, 0.0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return Response("Payload missing", status=400)
    
    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity', 1)

        if not product_code or not isinstance(quantity, int):
            return Response("Invalid payload structure", status=400)

        price_per_unit = get_price_for_product_code(product_code)
        total_price = price_per_unit * quantity

        response_data = {'total_price': total_price}
        yaml_response = yaml.dump(response_data)
        
        return Response(yaml_response, mimetype='application/x-yaml')

    except yaml.YAMLError:
        return Response("Error parsing YAML", status=400)

if __name__ == '__main__':
    app.run(debug=True)