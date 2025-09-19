from flask import Flask, request
import yaml

app = Flask(__name__)

PRICING = {
    'A1': 10,
    'B2': 20,
    'C3': 30
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    payload_yaml = request.args.get('payload')
    payload = yaml.safe_load(payload_yaml)
    product_code = payload['product_code']
    quantity = payload['quantity']
    price = PRICING[product_code]
    total_price = price * quantity
    return str(total_price)

if __name__ == '__main__':
    app.run(debug=True)