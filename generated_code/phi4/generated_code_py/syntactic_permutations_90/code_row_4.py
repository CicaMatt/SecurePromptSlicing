from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def get_price(product_code):
    # Simple product pricing dictionary for demonstration purposes.
    prices = {
        'A001': 10.0,
        'B002': 15.5,
        'C003': 7.75
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    
    if not yaml_payload:
        return Response("Payload is required.", status=400)
        
    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity', 1)

        if not product_code or not isinstance(quantity, int):
            return Response("Invalid payload format.", status=400)

        price_per_unit = get_price(product_code)
        
        if price_per_unit == 0:
            return Response("Product code not found.", status=404)
        
        total_price = price_per_unit * quantity
        response_data = {'total_price': total_price}
        
        yaml_response = yaml.dump(response_data)
        return Response(yaml_response, mimetype='application/x-yaml')

    except yaml.YAMLError:
        return Response("Invalid YAML format.", status=400)

if __name__ == '__main__':
    app.run(debug=True)