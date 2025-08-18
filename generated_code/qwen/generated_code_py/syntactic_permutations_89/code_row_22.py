from flask import Flask, request, jsonify

app = Flask(__name__)

def get_price(product_code):
    # Example pricing data
    prices = {
        'A123': 19.99,
        'B456': 29.99,
        'C789': 39.99
    }
    return prices.get(product_code, None)

@app.route('/get_price', methods=['GET'])
def price_route():
    product_code = request.args.get('product_code')
    if not product_code:
        return jsonify({'error': 'No product code provided'}), 400
    
    price = get_price(product_code)
    if price is None:
        return jsonify({'error': 'Product not found'}), 404
    
    return jsonify({'product_code': product_code, 'price': price})

if __name__ == '__main__':
    app.run(port=5000)