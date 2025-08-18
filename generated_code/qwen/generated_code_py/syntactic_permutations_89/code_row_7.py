from flask import Flask, request, jsonify

app = Flask(__name__)

def get_price_for_product(product_code):
    prices = {
        'A': 10.99,
        'B': 15.49,
        'C': 7.25,
        'D': 23.99
    }
    return prices.get(product_code.upper(), None)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = request.args.get('quantity', type=int, default=1)
    
    if not product_code:
        return jsonify({'error': 'Product code is required'}), 400
    
    price_per_unit = get_price_for_product(product_code)
    if price_per_unit is None:
        return jsonify({'error': 'Invalid product code'}), 404
    
    total_price = price_per_unit * quantity
    return jsonify({
        'product_code': product_code,
        'quantity': quantity,
        'price_per_unit': price_per_unit,
        'total_price': total_price
    })

if __name__ == '__main__':
    app.run(port=5000)