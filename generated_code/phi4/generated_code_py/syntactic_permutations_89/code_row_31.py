from flask import Flask, request

app = Flask(__name__)

# Dummy database of products with prices
product_prices = {
    'P001': 10.0,
    'P002': 15.5,
    'P003': 7.25,
}

def get_price(product_code):
    return product_prices.get(product_code, None)

@app.route('/price', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    
    price_per_unit = get_price(product_code)
    if price_per_unit is not None:
        total_price = price_per_unit * quantity
        return f'Total price for {quantity} units of product {product_code}: ${total_price:.2f}'
    else:
        return 'Product code not found', 404

if __name__ == '__main__':
    app.run(debug=True)