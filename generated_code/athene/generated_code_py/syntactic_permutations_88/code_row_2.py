import yaml
from flask import Flask, request

app = Flask(__name__)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    payload = request.args.get('payload')
    data = yaml.safe_load(payload)
    product = data['product']
    quantity = data['quantity']
    price = {
        'apple': 1.2,
        'banana': 0.5,
        'cherry': 0.2
    }[product]
    total_price = price * quantity
    return str(total_price)

if __name__ == '__main__':
    app.run(debug=True)