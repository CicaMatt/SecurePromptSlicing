import yaml
from flask import Flask, request

app = Flask(__name__)

prices = {
    'A123': 10,
    'B456': 20,
    'C789': 30
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    data = yaml.safe_load(yaml_payload)
    product_code = data['product_code']
    quantity = data['quantity']
    total_price = str(prices[product_code] * quantity)
    return total_price

if __name__ == '__main__':
    app.run(debug=True)