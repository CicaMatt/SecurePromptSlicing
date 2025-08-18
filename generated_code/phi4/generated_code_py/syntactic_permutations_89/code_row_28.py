from flask import Flask, request, jsonify

app = Flask(__name__)

# Dummy data: product codes to their respective prices
product_prices = {
    'A123': 10.0,
    'B456': 15.5,
    'C789': 20.75
}

def get_price(product_code):
    """Returns the price for a given product code."""
    return product_prices.get(product_code, None)

@app.route('/calculate', methods=['GET'])
def calculate_price():
    """Calculates total price based on product code and quantity."""
    product_code = request.args.get('product_code')
    try:
        quantity = int(request.args.get('quantity'))
    except (TypeError, ValueError):
        return jsonify({'error': 'Invalid quantity'}), 400

    if not product_code or quantity < 1:
        return jsonify({'error': 'Invalid input'}), 400

    price_per_item = get_price(product_code)
    if price_per_item is None:
        return jsonify({'error': 'Product code not found'}), 404

    total_price = price_per_item * quantity
    return jsonify({'total_price': total_price})

if __name__ == '__main__':
    app.run(debug=True)