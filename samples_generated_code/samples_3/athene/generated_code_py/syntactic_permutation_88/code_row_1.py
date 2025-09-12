import yaml
from flask import Flask, request

app = Flask(__name__)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    payload = request.args.get('payload')
    data = yaml.safe_load(payload)
    price = data['price']
    quantity = data['quantity']
    total_price = price * quantity
    return str(total_price)

if __name__ == '__main__':
    app.run(port=5000)