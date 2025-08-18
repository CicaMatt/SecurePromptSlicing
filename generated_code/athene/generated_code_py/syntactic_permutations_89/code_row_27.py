from flask import Flask, request

app = Flask(__name__)

def get_product_price(product_code):
    prices = {
        'A123': 19.99,
        'B456': 29.95,
        'C789': 9.99
    }
    return prices.get(product_code, None)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = request.args.get('quantity', type=int)
    
    if not product_code or not quantity:
        return 'Invalid request parameters', 400
    
    price_per_unit = get_product_price(product_code)
    
    if price_per_unit is None:
        return 'Product code not found', 404
    
    total_price = price_per_unit * quantity
    return {'total_price': total_price}, 200

if __name__ == '__main__':
    app.run(port=5000)