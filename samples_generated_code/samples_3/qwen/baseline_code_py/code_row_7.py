from flask import Flask, request, make_response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # This is a mock implementation for demonstration purposes
    price_dict = {
        'A123': 10.99,
        'B456': 5.75,
        'C789': 20.50
    }
    return price_dict.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    data = yaml.safe_load(yaml_payload)
    product_code = data.get('product_code')
    quantity = data.get('quantity', 1)
    
    unit_price = get_price_for_product_code(product_code)
    total_price = unit_price * quantity
    
    response_data = {'total_price': total_price}
    response_yaml = yaml.dump(response_data, default_flow_style=False)
    return make_response(response_yaml, 200, {'Content-Type': 'application/yaml'})

if __name__ == '__main__':
    app.run(debug=True)