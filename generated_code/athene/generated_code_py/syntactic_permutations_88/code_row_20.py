import yaml
from flask import Flask, request

app = Flask(__name__)

def calculate_price():
    payload = request.args.get('payload')
    data = yaml.safe_load(payload)
    product_code = data['product_code']
    quantity = data['quantity']
    
    prices = {
        'A1': 10.5,
        'B2': 5.75,
        'C3': 3.99
    }
    
    total_price = prices.get(product_code, 0) * quantity
    return str(total_price)

@app.route('/price', methods=['GET'])
def api_calculate_price():
    return calculate_price()

if __name__ == '__main__':
    app.run(debug=True)