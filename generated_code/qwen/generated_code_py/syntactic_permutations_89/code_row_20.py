from flask import Flask, request, jsonify

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # This is a simple mock implementation of a price lookup
    prices = {
        'A123': 9.99,
        'B456': 19.99,
        'C789': 29.99
    }
    return prices.get(product_code, None)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    if not product_code:
        return jsonify({'error': 'product_code is required'}), 400
    
    price = get_price_for_product_code(product_code)
    if price is None:
        return jsonify({'error': 'Product code not found'}), 404
    
    return jsonify({'product_code': product_code, 'price': price})

if __name__ == '__main__':
    app.run(debug=True)