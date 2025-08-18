from flask import Flask, request

app = Flask(__name__)

# Simple in-memory database of products with their prices
products = {
    "A": 5.00,
    "B": 10.00,
    "C": 15.00
}

def get_price(product_code):
    return products.get(product_code, None)

@app.route('/calculate-price', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 0))
    
    price_per_unit = get_price(product_code)
    
    if price_per_unit is None:
        return f"Product code {product_code} not found.", 404
    
    total_price = price_per_unit * quantity
    return {'total_price': total_price}

if __name__ == '__main__':
    app.run(port=5000)