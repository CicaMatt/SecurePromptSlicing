from flask import Flask, request, make_response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    prices = {
        'A001': 19.99,
        'B002': 5.49,
        'C003': 3.75
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return make_response("No payload provided", 400)
    
    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity', 1)
        
        if not product_code:
            return make_response("Product code is required", 400)
        
        price_per_unit = get_price_for_product_code(product_code)
        total_price = price_per_unit * quantity
        
        response_data = {'total_price': total_price}
        response_yaml = yaml.dump(response_data, default_flow_style=False)
        return make_response(response_yaml, 200)
    
    except yaml.YAMLError as e:
        return make_response(f"Error parsing YAML: {e}", 400)

if __name__ == '__main__':
    app.run(debug=True)