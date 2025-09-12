import yaml
from flask import Flask, request

app = Flask(__name__)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    payload = request.args.get('payload')
    data = yaml.safe_load(payload)
    product_code = data['product_code']
    quantity = data['quantity']
    prices = {
        'A1': 10.5,
        'B2': 5.75,
        'C3': 20
    }
    total_price = str(prices[product_code] * quantity)
    return total_price

if __name__ == '__main__':
    app.run(debug=True)