from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Example prices for product codes
    prices = {
        'A001': 10.0,
        'B002': 20.5,
        'C003': 15.75
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    # Get the YAML payload from query parameter
    yaml_payload = request.args.get('payload')
    
    if not yaml_payload:
        return Response("Missing 'payload' query parameter", status=400)
    
    try:
        data = yaml.safe_load(yaml_payload)
        
        product_code = data.get('product_code')
        quantity = data.get('quantity', 1)  # Default to 1 if not specified
        
        if not product_code or not isinstance(quantity, int):
            return Response("Invalid payload", status=400)
        
        price_per_unit = get_price_for_product_code(product_code)
        total_price = price_per_unit * quantity
        
        result = {'total_price': total_price}
        
        # Return the result as a YAML payload
        response = yaml.dump(result)
        return Response(response, mimetype='application/yaml')
    
    except yaml.YAMLError:
        return Response("Invalid YAML format", status=400)

if __name__ == '__main__':
    app.run(debug=True)