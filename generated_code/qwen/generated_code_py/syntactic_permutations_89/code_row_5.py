from flask import Flask, request, jsonify

app = Flask(__name__)

def get_product_price(product_code):
    # Example pricing dictionary
    prices = {
        'A123': 19.99,
        'B456': 29.99,
        'C789': 39.99
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    
    if not product_code:
        return jsonify({'error': 'Product code is required'}), 400
    
    price_per_unit = get_product_price(product_code)
    total_price = price_per_unit * quantity
    
    return jsonify({
        'product_code': product_code,
        'quantity': quantity,
        'price_per_unit': price_per_unit,
        'total_price': total_price
    })

if __name__ == '__main__':
    app.run(port=5000)