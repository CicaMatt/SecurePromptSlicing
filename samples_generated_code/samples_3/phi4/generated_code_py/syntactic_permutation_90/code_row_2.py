from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def get_price(product_code):
    # Example pricing dictionary
    pricing = {
        'A001': 10.0,
        'B002': 15.5,
        'C003': 7.25
    }
    return pricing.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return Response("Payload is required", status=400)
    
    try:
        data = yaml.safe_load(yaml_payload)
    except yaml.YAMLError as e:
        return Response(f"Invalid YAML: {str(e)}", status=400)

    product_code = data.get('product_code')
    quantity = data.get('quantity', 1)  # Default to 1 if not provided

    if not isinstance(quantity, int) or quantity < 1:
        return Response("Quantity must be a positive integer", status=400)
    
    price_per_unit = get_price(product_code)
    if price_per_unit == 0:
        return Response("Invalid product code", status=404)

    total_price = price_per_unit * quantity

    result = {'total_price': total_price}
    response_yaml = yaml.dump(result)
    
    return Response(response_yaml, mimetype='application/x-yaml')

if __name__ == '__main__':
    app.run(debug=True)