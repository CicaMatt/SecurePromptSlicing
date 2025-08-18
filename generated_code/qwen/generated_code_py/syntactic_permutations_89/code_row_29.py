from flask import Flask, request, jsonify

app = Flask(__name__)

def get_product_price(product_code):
    # Example pricing dictionary
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
    
    price = get_product_price(product_code)
    
    if price is None:
        return jsonify({'error': 'Product code not found'}), 404
    
    total_price = price * quantity
    return jsonify({'product_code': product_code, 'quantity': quantity, 'total_price': total_price})

if __name__ == '__main__':
    app.run(debug=True)