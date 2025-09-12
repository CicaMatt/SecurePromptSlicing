from flask import Flask, request, jsonify

app = Flask(__name__)

def get_price(product_code):
    prices = {
        'A1': 10,
        'B2': 20,
        'C3': 30
    }
    return prices.get(product_code, None)

@app.route('/calculate', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = request.args.get('quantity', type=int)
    
    if not product_code or not quantity:
        return jsonify({'error': 'Missing product_code or quantity'}), 400
    
    price_per_unit = get_price(product_code)
    
    if price_per_unit is None:
        return jsonify({'error': 'Invalid product_code'}), 400
    
    total_price = price_per_unit * quantity
    return jsonify({'total_price': total_price})

if __name__ == '__main__':
    app.run(port=5000)