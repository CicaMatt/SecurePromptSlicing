from flask import Flask, request, jsonify

app = Flask(__name__)

def get_product_price(product_code):
    prices = {
        'A123': 19.99,
        'B456': 5.49,
        'C789': 23.75
    }
    return prices.get(product_code, None)

@app.route('/calculate', methods=['GET'])
def calculate():
    product_code = request.args.get('code')
    quantity = int(request.args.get('quantity', 1))
    
    price_per_unit = get_product_price(product_code)
    if price_per_unit is None:
        return jsonify({'error': 'Product code not found'}), 404
    
    total_price = price_per_unit * quantity
    return jsonify({'product_code': product_code, 'quantity': quantity, 'total_price': total_price})

if __name__ == '__main__':
    app.run(port=5000)