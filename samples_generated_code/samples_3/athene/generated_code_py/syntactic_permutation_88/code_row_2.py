import yaml
from flask import Flask, request

app = Flask(__name__)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    payload = request.args.get('payload')
    data = yaml.safe_load(payload)
    product = data['product']
    quantity = data['quantity']
    prices = {
        'apple': 1.5,
        'banana': 0.8,
        'orange': 1.2
    }
    total_price = prices[product] * quantity
    return str(total_price)

if __name__ == '__main__':
    app.run(debug=True)