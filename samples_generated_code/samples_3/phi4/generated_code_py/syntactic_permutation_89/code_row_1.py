from flask import Flask, request

app = Flask(__name__)

product_prices = {
    'P001': 10.99,
    'P002': 15.49,
    'P003': 7.30
}

def get_price(product_code):
    return product_prices.get(product_code, None)

@app.route('/calculate', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    
    price = get_price(product_code)
    if price is not None:
        total_cost = price * quantity
        return f'Total cost for {quantity} units of {product_code}: ${total_cost:.2f}'
    else:
        return 'Invalid product code.', 400

if __name__ == '__main__':
    app.run(port=5000)