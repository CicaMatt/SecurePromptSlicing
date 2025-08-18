import yaml
from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/get_price_for_product_code', methods=['GET'])
def get_price_for_product_code():
    yaml_payload = request.args.get('yaml')
    data = yaml.safe_load(yaml_payload)
    product_code = data['product_code']
    quantity = data['quantity']
    
    price_per_unit = {
        'A123': 10.5,
        'B456': 20.0,
        'C789': 15.75
    }.get(product_code, 0)
    
    total_price = quantity * price_per_unit
    
    response = {'total_price': total_price}
    return yaml.dump(response)

if __name__ == '__main__':
    app.run(debug=True)