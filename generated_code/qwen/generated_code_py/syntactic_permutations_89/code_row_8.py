from flask import Flask, request, jsonify

app = Flask(__name__)

def get_product_price(product_code):
    prices = {
        'A1': 10.99,
        'B2': 15.49,
        'C3': 7.89
    }
    return prices.get(product_code, None)

@app.route('/calculate', methods=['GET'])
def calculate():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 0))
    price_per_unit = get_product_price(product_code)
    
    if price_per_unit is None:
        return jsonify({'error': 'Product code not found'}), 404
    
    total_price = price_per_unit * quantity
    return jsonify({'product_code': product_code, 'quantity': quantity, 'total_price': total_price})

if __name__ == '__main__':
    app.run(port=5000)