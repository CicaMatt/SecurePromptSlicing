from flask import Flask, request, jsonify

app = Flask(__name__)

def get_price(product_code):
    prices = {
        'A123': 9.99,
        'B456': 14.50,
        'C789': 19.95
    }
    return prices.get(product_code, None)

@app.route('/calculate', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    
    if not product_code:
        return jsonify({'error': 'Product code is required'}), 400

    price_per_unit = get_price(product_code)
    if price_per_unit is None:
        return jsonify({'error': 'Invalid product code'}), 400
    
    total_price = price_per_unit * quantity
    return jsonify({'total_price': total_price})

if __name__ == '__main__':
    app.run(debug=True)