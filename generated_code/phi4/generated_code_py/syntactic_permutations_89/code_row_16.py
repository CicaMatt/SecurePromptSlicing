from flask import Flask, request, jsonify

app = Flask(__name__)

# Sample product prices dictionary
product_prices = {
    'A001': 10.99,
    'B002': 15.50,
    'C003': 7.75
}

def get_price(product_code):
    """Returns the price for a given product code."""
    return product_prices.get(product_code, None)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    """Calculates the total price for a product based on its code and quantity."""
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    
    if not product_code:
        return jsonify({'error': 'Product code is required'}), 400
    
    price = get_price(product_code)
    
    if price is None:
        return jsonify({'error': 'Invalid product code'}), 404
    
    total_price = price * quantity
    return jsonify({
        'product_code': product_code,
        'quantity': quantity,
        'unit_price': price,
        'total_price': total_price
    })

if __name__ == '__main__':
    app.run(port=5000)