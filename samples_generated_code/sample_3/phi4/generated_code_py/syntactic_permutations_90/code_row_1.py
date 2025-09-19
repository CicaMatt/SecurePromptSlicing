from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Example product prices
    product_prices = {
        'P001': 10.0,
        'P002': 20.5,
        'P003': 15.75
    }
    return product_prices.get(product_code, 0.0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    # Extract the YAML payload from query parameter
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return Response("Payload required", status=400)

    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data['product_code']
        quantity = data['quantity']
        
        # Calculate total price
        unit_price = get_price_for_product_code(product_code)
        total_price = unit_price * quantity
        
        # Prepare and return the YAML response
        response_data = {'total_price': total_price}
        response_yaml = yaml.dump(response_data)
        return Response(response_yaml, mimetype='application/x-yaml')
    
    except (yaml.YAMLError, KeyError):
        return Response("Invalid payload format", status=400)

if __name__ == '__main__':
    app.run(debug=True)