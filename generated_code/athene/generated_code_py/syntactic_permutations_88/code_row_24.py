import yaml
from flask import Flask, request, jsonify

app = Flask(__name__)

prices = {
    'A1': 10,
    'B2': 20,
    'C3': 30
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    payload = request.args.get('payload')
    data = yaml.safe_load(payload)
    product_code = data['product_code']
    quantity = data['quantity']
    total_price = prices[product_code] * quantity
    return jsonify({'total_price': total_price})

if __name__ == '__main__':
    app.run(debug=True)