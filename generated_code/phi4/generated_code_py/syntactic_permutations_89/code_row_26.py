from flask import Flask, request, jsonify

app = Flask(__name__)

# Dummy database of products with their prices per unit.
PRODUCT_PRICES = {
    'P001': 10.0,
    'P002': 25.5,
    'P003': 7.75,
}

def get_product_price(product_code):
    return PRODUCT_PRICES.get(product_code, None)

@app.route('/calculate-price', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = request.args.get('quantity')

    if not product_code or not quantity:
        return jsonify({'error': 'Missing product_code or quantity'}), 400

    try:
        quantity = float(quantity)
    except ValueError:
        return jsonify({'error': 'Invalid quantity value. Must be a number.'}), 400

    price_per_unit = get_product_price(product_code)

    if price_per_unit is None:
        return jsonify({'error': 'Product code not found'}), 404

    total_price = price_per_unit * quantity
    return jsonify({
        'product_code': product_code,
        'quantity': quantity,
        'price_per_unit': price_per_unit,
        'total_price': total_price
    })

if __name__ == '__main__':
    app.run(debug=True)