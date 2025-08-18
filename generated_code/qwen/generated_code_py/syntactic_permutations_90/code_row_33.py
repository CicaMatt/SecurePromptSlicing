from flask import Flask, request, make_response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    prices = {
        'A123': 10.99,
        'B456': 5.75,
        'C789': 20.00
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return "No payload provided", 400
    
    try:
        data = yaml.safe_load(yaml_payload)
    except yaml.YAMLError as exc:
        return f"Error parsing YAML: {exc}", 400

    product_code = data.get('product_code')
    quantity = data.get('quantity')

    if not product_code or not quantity:
        return "Invalid payload", 400
    
    price_per_unit = get_price_for_product_code(product_code)
    total_price = price_per_unit * quantity

    response_data = {'total_price': total_price}
    yaml_response = yaml.dump(response_data, default_flow_style=False)

    response = make_response(yaml_response)
    response.headers['Content-Type'] = 'application/yaml'
    return response

if __name__ == '__main__':
    app.run(debug=True)