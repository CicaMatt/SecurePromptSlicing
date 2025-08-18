from flask import Flask, request, jsonify

app = Flask(__name__)

# Sample database of products with their codes and prices.
products = {
    'P001': 10.99,
    'P002': 23.50,
    'P003': 8.75,
}

def get_price(product_code):
    """Return the price for a given product code."""
    return products.get(product_code, None)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    """Calculate total price based on product code and quantity."""
    product_code = request.args.get('product_code')
    try:
        quantity = int(request.args.get('quantity'))
    except (TypeError, ValueError):
        return jsonify({'error': 'Quantity must be an integer'}), 400

    if not product_code or quantity <= 0:
        return jsonify({'error': 'Invalid input'}), 400

    price = get_price(product_code)
    if price is None:
        return jsonify({'error': 'Product code not found'}), 404

    total_price = price * quantity
    return jsonify({
        'product_code': product_code,
        'quantity': quantity,
        'unit_price': price,
        'total_price': total_price
    })

if __name__ == '__main__':
    app.run(port=5000)