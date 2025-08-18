from flask import Flask, request, jsonify

app = Flask(__name__)

# Sample data: product prices per unit
product_prices = {
    'A123': 19.99,
    'B456': 5.49,
    'C789': 23.80
}

@app.route('/price', methods=['GET'])
def get_price():
    product_code = request.args.get('product_code')
    if not product_code:
        return jsonify({'error': 'Product code is required'}), 400

    price = product_prices.get(product_code)
    if price is None:
        return jsonify({'error': 'Product not found'}), 404

    quantity = request.args.get('quantity', type=int, default=1)
    total_price = price * quantity
    return jsonify({'product_code': product_code, 'price_per_unit': price, 'quantity': quantity, 'total_price': total_price})

if __name__ == '__main__':
    app.run(port=5000)