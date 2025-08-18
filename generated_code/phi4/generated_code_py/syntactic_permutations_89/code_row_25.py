from flask import Flask, request

app = Flask(__name__)

# A simple dictionary to simulate product codes and their prices.
product_prices = {
    'A001': 10.99,
    'B002': 23.50,
    'C003': 5.75
}

def get_price(product_code):
    return product_prices.get(product_code, None)

@app.route('/calculate-price', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    
    price_per_unit = get_price(product_code)
    if price_per_unit is None:
        return f"Product code {product_code} not found.", 404

    total_price = price_per_unit * quantity
    return {'total_price': total_price}

if __name__ == '__main__':
    app.run(port=5000)