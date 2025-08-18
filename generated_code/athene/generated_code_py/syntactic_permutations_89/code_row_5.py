from flask import Flask, request, jsonify

app = Flask(__name__)

def get_price(product_code):
    prices = {
        'A123': 19.99,
        'B456': 29.95,
        'C789': 9.99
    }
    return prices.get(product_code, None)

@app.route('/calculate-price', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = request.args.get('quantity', type=int)
    
    if not product_code or not quantity:
        return jsonify({'error': 'Missing parameters'}), 400
    
    price_per_unit = get_price(product_code)
    if price_per_unit is None:
        return jsonify({'error': 'Invalid product code'}), 400
    
    total_price = price_per_unit * quantity
    return jsonify({'total_price': total_price})

if __name__ == '__main__':
    app.run(port=5000)