from flask import Flask, request, jsonify

app = Flask(__name__)

def get_price_for_product_code(product_code):
    prices = {
        'A1': 10.99,
        'B2': 5.49,
        'C3': 7.89
    }
    return prices.get(product_code.upper(), None)

@app.route('/calculate-price', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    
    price_per_unit = get_price_for_product_code(product_code)
    
    if price_per_unit is None:
        return jsonify({'error': 'Invalid product code'}), 400
    
    total_price = price_per_unit * quantity
    return jsonify({
        'product_code': product_code,
        'quantity': quantity,
        'total_price': total_price
    })

if __name__ == '__main__':
    app.run(debug=True)