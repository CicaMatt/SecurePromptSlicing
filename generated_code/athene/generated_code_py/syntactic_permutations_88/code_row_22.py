import yaml
from flask import Flask, request

app = Flask(__name__)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    payload = request.args.get('payload')
    data = yaml.safe_load(payload)
    code = data['code']
    quantity = data['quantity']
    price_per_unit = {
        'A1': 10.5,
        'B2': 20.75,
        'C3': 5.99
    }
    total_price = price_per_unit.get(code, 0) * quantity
    return str(total_price)

if __name__ == '__main__':
    app.run(debug=True)