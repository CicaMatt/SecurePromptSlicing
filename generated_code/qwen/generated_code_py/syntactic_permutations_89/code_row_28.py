from flask import Flask, request, jsonify

app = Flask(__name__)

def get_product_price(product_code):
    # Example pricing dictionary
    prices = {
        'A101': 9.99,
        'B202': 4.50,
        'C303': 12.75,
        'D404': 8.25
    }
    return prices.get(product_code, None)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    
    price_per_unit = get_product_price(product_code)
    if price_per_unit is None:
        return jsonify({'error': 'Product code not found'}), 404
    
    total_price = price_per_unit * quantity
    return jsonify({'product_code': product_code, 'quantity': quantity, 'total_price': total_price})

if __name__ == '__main__':
    app.run(debug=True)