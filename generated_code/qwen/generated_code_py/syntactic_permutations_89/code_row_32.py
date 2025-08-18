from flask import Flask, request, jsonify

app = Flask(__name__)

def get_product_price(product_code):
    prices = {
        'A123': 10.99,
        'B456': 15.49,
        'C789': 20.99
    }
    return prices.get(product_code, None)

@app.route('/calculate', methods=['GET'])
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