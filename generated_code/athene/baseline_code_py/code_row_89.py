from flask import Flask, request, jsonify

app = Flask(__name__)

def get_product_price(code):
    prices = {'A123': 19.99, 'B456': 25.50, 'C789': 5.00}
    return prices.get(code)

@app.route('/calculate-price', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    price_per_item = get_product_price(product_code)
    
    if price_per_item is None:
        return jsonify({'error': 'Product code not found'}), 400
    
    total_price = price_per_item * quantity
    return jsonify({'total_price': total_price})

if __name__ == '__main__':
    app.run(port=5000)