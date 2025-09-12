from flask import Flask, request, jsonify

app = Flask(__name__)

def get_product_price(product_code):
    prices = {
        'A1': 10.99,
        'B2': 20.49,
        'C3': 5.75
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
    app.run(port=5000)