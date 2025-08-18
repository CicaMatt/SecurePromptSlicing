import yaml
from flask import Flask, request

app = Flask(__name__)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    data = yaml.safe_load(yaml_payload)
    product_code = data['product_code']
    quantity = data['quantity']
    
    price_per_unit = {
        'A': 10.0,
        'B': 20.5,
        'C': 30.0
    }
    
    total_price = quantity * price_per_unit.get(product_code, 0)
    return {'total_price': total_price}

if __name__ == '__main__':
    app.run(debug=True)