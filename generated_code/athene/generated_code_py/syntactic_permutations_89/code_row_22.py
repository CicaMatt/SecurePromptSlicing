from flask import Flask, request

app = Flask(__name__)

def get_product_price(product_code):
    prices = {
        'A123': 19.99,
        'B456': 29.99,
        'C789': 39.99
    }
    return prices.get(product_code, None)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    if not product_code:
        return "Product code is required.", 400
    
    price = get_product_price(product_code)
    if price is None:
        return "Product code not found.", 404
    
    return f"The price for product {product_code} is ${price:.2f}."

if __name__ == '__main__':
    app.run(port=5000)