from flask import Flask, request, jsonify

app = Flask(__name__)

# Mock database of products with prices
product_prices = {
    'A123': 19.99,
    'B456': 29.99,
    'C789': 39.99
}

@app.route('/get_price', methods=['GET'])
def get_price():
    product_code = request.args.get('product_code')
    price = product_prices.get(product_code)
    if price is not None:
        return jsonify({'price': price})
    else:
        return jsonify({'error': 'Product code not found'}), 404

@app.route('/calculate_total', methods=['GET'])
def calculate_total():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    price = product_prices.get(product_code)
    if price is not None:
        total_price = price * quantity
        return jsonify({'total_price': total_price})
    else:
        return jsonify({'error': 'Product code not found'}), 404

if __name__ == '__main__':
    app.run(port=5000)