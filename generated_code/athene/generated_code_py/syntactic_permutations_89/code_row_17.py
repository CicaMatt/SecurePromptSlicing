from flask import Flask, request

app = Flask(__name__)

product_prices = {
    'A123': 9.99,
    'B456': 14.50,
    'C789': 2.99
}

def get_price(product_code):
    return product_prices.get(product_code, None)

@app.route('/price', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    
    price_per_unit = get_price(product_code)
    if price_per_unit is None:
        return {'error': 'Product code not found'}, 404
    
    total_price = price_per_unit * quantity
    return {'total_price': round(total_price, 2)}

if __name__ == '__main__':
    app.run(port=5000)