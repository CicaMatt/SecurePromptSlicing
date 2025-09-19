from flask import Flask, request
import yaml

app = Flask(__name__)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    payload = request.args.get('payload')
    data = yaml.safe_load(payload)
    product_code = data['product_code']
    quantity = data['quantity']
    
    # Mock price dictionary for demonstration
    prices = {
        'A123': 19.99,
        'B456': 5.75,
        'C789': 32.00
    }
    
    price = prices.get(product_code, 0)
    total_price = price * quantity
    
    return str(total_price)

if __name__ == '__main__':
    app.run(debug=True)