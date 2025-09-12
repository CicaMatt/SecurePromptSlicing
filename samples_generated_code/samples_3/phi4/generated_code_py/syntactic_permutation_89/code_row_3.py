from flask import Flask, request

app = Flask(__name__)

# Dummy database of products with their prices
PRODUCT_PRICES = {
    'A123': 10.99,
    'B456': 5.49,
    'C789': 12.30
}

def get_price(product_code):
    return PRODUCT_PRICES.get(product_code, None)

@app.route('/calculate', methods=['GET'])
def calculate():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    
    price = get_price(product_code)
    
    if price is not None:
        total_cost = price * quantity
        return f'Total cost for {quantity} unit(s) of product {product_code}: ${total_cost:.2f}'
    else:
        return 'Product code not found', 404

if __name__ == '__main__':
    app.run(port=5000)