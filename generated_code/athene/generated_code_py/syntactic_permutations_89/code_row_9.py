from flask import Flask, request

app = Flask(__name__)

prices = {
    'A123': 19.99,
    'B456': 29.95,
    'C789': 9.99
}

@app.route('/price', methods=['GET'])
def get_price():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    
    if product_code in prices:
        total_price = prices[product_code] * quantity
        return {'total_price': total_price}
    else:
        return {'error': 'Product code not found'}, 404

if __name__ == '__main__':
    app.run(port=5000)