import yaml
from flask import Flask, request

app = Flask(__name__)

prices = {
    'A1': 10,
    'B2': 20,
    'C3': 30
}

@app.route('/calculate_price', methods=['POST'])
def calculate_price():
    payload = yaml.safe_load(request.data)
    product_code = payload['product_code']
    quantity = payload['quantity']
    total_price = str(prices[product_code] * quantity)
    return total_price

if __name__ == '__main__':
    app.run(debug=True)