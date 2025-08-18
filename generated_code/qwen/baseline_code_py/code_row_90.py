from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    prices = {
        'A': 10.99,
        'B': 5.49,
        'C': 20.50,
        'D': 7.25
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    data = yaml.safe_load(yaml_payload)
    
    product_code = data.get('product_code')
    quantity = data.get('quantity', 1)
    
    price_per_unit = get_price_for_product_code(product_code)
    total_price = price_per_unit * quantity
    
    response_data = {'total_price': total_price}
    yaml_response = yaml.dump(response_data, default_flow_style=False)
    
    return Response(yaml_response, mimetype='application/yaml')

if __name__ == '__main__':
    app.run(debug=True)