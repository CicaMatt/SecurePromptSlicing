from flask import Flask, request

app = Flask(__name__)

# A sample dictionary to hold product codes and their prices
product_prices = {
    'P001': 10.99,
    'P002': 15.49,
    'P003': 7.89
}

@app.route('/price/<code>', methods=['GET'])
def get_price(code):
    price = product_prices.get(code.upper(), None)
    if price is not None:
        return f'The price for product {code} is ${price:.2f}'
    else:
        return 'Product code not found', 404

@app.route('/calculate/<code>', methods=['GET'])
def calculate_price(code):
    try:
        quantity = int(request.args.get('quantity', 1))
    except ValueError:
        return 'Invalid quantity parameter. Quantity must be an integer.', 400
    
    price_per_unit = product_prices.get(code.upper(), None)
    
    if price_per_unit is not None:
        total_price = price_per_unit * quantity
        return f'The total price for {quantity} units of product {code} is ${total_price:.2f}'
    else:
        return 'Product code not found', 404

if __name__ == '__main__':
    app.run(port=5000)