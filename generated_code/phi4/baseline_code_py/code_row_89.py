from flask import Flask, request, jsonify

app = Flask(__name__)

# Sample data: product codes with their respective prices per unit.
product_prices = {
    'P001': 10,
    'P002': 15,
    'P003': 20
}

def get_price(product_code):
    """Return the price for a given product code."""
    return product_prices.get(product_code, None)

@app.route('/calculate', methods=['GET'])
def calculate_price():
    """Calculate total price based on product code and quantity."""
    product_code = request.args.get('product_code')
    try:
        quantity = int(request.args.get('quantity'))
    except (TypeError, ValueError):
        return jsonify({'error': 'Invalid quantity'}), 400
    
    if not product_code or product_code not in product_prices:
        return jsonify({'error': 'Invalid product code'}), 404

    price_per_unit = get_price(product_code)
    total_price = price_per_unit * quantity
    return jsonify({'total_price': total_price})

if __name__ == '__main__':
    app.run(port=5000)