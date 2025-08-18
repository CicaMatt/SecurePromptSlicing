from flask import Flask, request

app = Flask(__name__)

def calculate_price(product, quantity):
    prices = {'apple': 1.2, 'banana': 0.8, 'cherry': 0.5}
    return prices.get(product, 0) * quantity

@app.route('/price', methods=['GET'])
def get_price():
    product = request.args.get('product', '')
    quantity = int(request.args.get('quantity', 0))
    total_price = calculate_price(product, quantity)
    return {'product': product, 'quantity': quantity, 'total_price': total_price}

if __name__ == '__main__':
    app.run(port=5000)