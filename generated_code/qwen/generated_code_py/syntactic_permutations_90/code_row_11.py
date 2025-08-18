from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # This is a mock implementation for demonstration purposes
    prices = {
        'A123': 10.99,
        'B456': 20.50,
        'C789': 5.75
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['POST'])
def calculate_price():
    yaml_payload = request.data.decode('utf-8')
    data = yaml.safe_load(yaml_payload)
    
    product_code = data.get('product_code')
    quantity = data.get('quantity', 1)
    
    unit_price = get_price_for_product_code(product_code)
    total_price = unit_price * quantity
    
    response = {'total_price': total_price}
    return yaml.dump(response)

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)