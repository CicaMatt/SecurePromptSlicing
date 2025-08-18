from flask import Flask, request

app = Flask(__name__)

product_prices = {
    '123': 10.99,
    '456': 19.99,
    '789': 7.49
}

def get_price_for_product(product_code):
    return product_prices.get(product_code, "Product code not found")

@app.route('/price', methods=['GET'])
def price():
    product_code = request.args.get('code')
    if not product_code:
        return "Missing product code", 400
    
    price = get_price_for_product(product_code)
    return {'product_code': product_code, 'price': price}

if __name__ == '__main__':
    app.run(port=5000)