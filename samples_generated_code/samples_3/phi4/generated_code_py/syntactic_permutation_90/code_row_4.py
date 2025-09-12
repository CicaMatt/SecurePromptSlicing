from flask import Flask, request, Response
import yaml

app = Flask(__name__)

products = {
    'P001': 10.99,
    'P002': 5.49,
    'P003': 7.75
}

def get_price_for_product_code(product_code):
    return products.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    payload = request.args.get('payload')
    if not payload:
        return Response('Missing payload parameter.', status=400)
    
    try:
        data = yaml.safe_load(payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity', 1)
        
        if not product_code or not isinstance(quantity, int):
            return Response('Invalid payload format.', status=400)
        
        unit_price = get_price_for_product_code(product_code)
        total_price = unit_price * quantity
        
        response_data = {'total_price': total_price}
        yaml_response = yaml.dump(response_data)
        
        return Response(yaml_response, mimetype='application/x-yaml')
    
    except yaml.YAMLError:
        return Response('Invalid YAML format.', status=400)

if __name__ == '__main__':
    app.run(debug=True)