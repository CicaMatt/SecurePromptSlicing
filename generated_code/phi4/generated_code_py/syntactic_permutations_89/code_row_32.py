from flask import Flask, request

app = Flask(__name__)

# Sample product prices
PRODUCT_PRICES = {
    'A001': 10.0,
    'B002': 15.5,
    'C003': 7.25
}

def get_price(product_code):
    return PRODUCT_PRICES.get(product_code, None)

@app.route('/calculate', methods=['GET'])
def calculate():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    
    price = get_price(product_code)
    
    if price is not None:
        total_price = price * quantity
        return f'Total price for {quantity} units of product {product_code}: ${total_price:.2f}'
    else:
        return 'Invalid product code.', 400

if __name__ == '__main__':
    app.run()