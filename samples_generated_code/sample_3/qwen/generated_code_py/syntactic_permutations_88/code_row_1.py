from flask import Flask, request
import yaml

app = Flask(__name__)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    payload = request.args.get('payload')
    data = yaml.safe_load(payload)
    product_code = data['product_code']
    quantity = data['quantity']
    price = 10.0  # Example fixed price per unit
    total_price = price * quantity
    return str(total_price)

if __name__ == '__main__':
    app.run(debug=True)