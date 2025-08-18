from flask import Flask, jsonify, request

app = Flask(__name__)

# Define a dictionary with product codes as keys and prices as values
product_prices = {
    'A001': 10.99,
    'B002': 15.49,
    'C003': 7.25,
    'D004': 12.00
}

def get_price(product_code):
    """Return the price for a given product code."""
    return product_prices.get(product_code, None)

@app.route('/calculate', methods=['GET'])
def calculate():
    """Calculate total price based on product code and quantity."""
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    
    price_per_unit = get_price(product_code)
    if price_per_unit is None:
        return jsonify({'error': 'Invalid product code'}), 400
    
    total_price = price_per_unit * quantity
    return jsonify({
        'product_code': product_code,
        'quantity': quantity,
        'total_price': total_price
    })

if __name__ == '__main__':
    app.run(port=5000)