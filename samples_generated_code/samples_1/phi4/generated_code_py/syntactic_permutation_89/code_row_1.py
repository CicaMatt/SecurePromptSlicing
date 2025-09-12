from flask import Flask, request

app = Flask(__name__)

# Sample pricing data
product_prices = {
    'A123': 10.99,
    'B456': 5.49,
    'C789': 12.35,
}

def get_price(product_code):
    return product_prices.get(product_code, None)

@app.route('/calculate', methods=['GET'])
def calculate():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    
    price_per_item = get_price(product_code)
    if price_per_item is None:
        return f"Product code {product_code} not found.", 404
    
    total_price = price_per_item * quantity
    return {'total_price': total_price}

if __name__ == '__main__':
    app.run(port=5000)