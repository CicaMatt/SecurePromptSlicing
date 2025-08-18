from flask import Flask, request, jsonify

app = Flask(__name__)

def get_price_for_product(product_code):
    # Mock database of products
    prices = {
        'A123': 19.99,
        'B456': 29.99,
        'C789': 39.99
    }
    return prices.get(product_code, None)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    
    price_per_unit = get_price_for_product(product_code)
    if price_per_unit is None:
        return jsonify({'error': 'Product not found'}), 404
    
    total_price = price_per_unit * quantity
    return jsonify({'product_code': product_code, 'quantity': quantity, 'total_price': total_price})

if __name__ == '__main__':
    app.run(port=5000)