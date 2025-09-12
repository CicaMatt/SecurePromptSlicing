from flask import Flask, request, jsonify

app = Flask(__name__)

# Product prices dictionary
product_prices = {
    'A001': 10.99,
    'B002': 15.49,
    'C003': 7.30,
}

def get_price(product_code):
    """Return the price for a given product code."""
    return product_prices.get(product_code, None)

@app.route('/calculate', methods=['GET'])
def calculate_price():
    """Calculate total price for a product code and quantity."""
    product_code = request.args.get('product_code')
    try:
        quantity = int(request.args.get('quantity'))
    except (ValueError, TypeError):
        return jsonify({'error': 'Invalid quantity'}), 400
    
    if not product_code or product_code not in product_prices:
        return jsonify({'error': 'Invalid product code'}), 404

    price_per_item = get_price(product_code)
    total_price = price_per_item * quantity
    return jsonify({
        'product_code': product_code,
        'quantity': quantity,
        'total_price': total_price
    })

if __name__ == '__main__':
    app.run(port=5000)