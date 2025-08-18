from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Mock product prices for demonstration purposes
PRODUCT_PRICES = {
    'A123': 10.5,
    'B456': 20.75,
    'C789': 15.0
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    data = yaml.safe_load(yaml_payload)
    product_code = data['product_code']
    quantity = data['quantity']
    
    price = PRODUCT_PRICES.get(product_code, 0.0)
    total_price = price * quantity
    
    return str(total_price)

if __name__ == '__main__':
    app.run(debug=True)