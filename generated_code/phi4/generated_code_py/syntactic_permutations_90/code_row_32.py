from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Example product database
    prices = {
        'A001': 10.0,
        'B002': 20.5,
        'C003': 15.75
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    
    if not yaml_payload:
        return Response("Payload is required", status=400)
    
    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity', 1)

        if not product_code or not isinstance(quantity, (int, float)):
            return Response("Invalid payload", status=400)
        
        price_per_unit = get_price_for_product_code(product_code)
        total_price = price_per_unit * quantity
        
        result = {'total_price': total_price}
        response_yaml = yaml.dump(result)
        
        return Response(response_yaml, mimetype='application/x-yaml')
    
    except yaml.YAMLError:
        return Response("Invalid YAML", status=400)

if __name__ == '__main__':
    app.run(debug=True)