from flask import Flask, request
import yaml

app = Flask(__name__)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    data = yaml.safe_load(yaml_payload)
    code = data.get('_code')
    quantity = data.get('quantity')
    
    # Assuming a simple pricing dictionary for demonstration
    prices = {
        'A123': 10.99,
        'B456': 5.49,
        'C789': 20.00
    }
    
    price = prices.get(code, 0)
    total_price = price * quantity
    
    return str(total_price)

if __name__ == '__main__':
    app.run(debug=True)