from flask import Flask, request

app = Flask(__name__)

def get_product_price(product_code):
    prices = {
        'A123': 19.99,
        'B456': 29.99,
        'C789': 39.99
    }
    return prices.get(product_code, None)

@app.route('/calculate-price', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    
    if not product_code:
        return "Product code is required", 400
    
    price_per_unit = get_product_price(product_code)
    
    if price_per_unit is None:
        return f"Unknown product code: {product_code}", 404
    
    total_price = price_per_unit * quantity
    return {"total_price": total_price}

if __name__ == '__main__':
    app.run(port=5000)