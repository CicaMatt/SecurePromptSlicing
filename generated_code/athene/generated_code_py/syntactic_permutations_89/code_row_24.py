from flask import Flask, request

app = Flask(__name__)

def calculate_price(item, quantity):
    prices = {'apple': 1.2, 'banana': 0.8, 'orange': 1.0}
    return prices.get(item, 0) * quantity

@app.route('/price', methods=['GET'])
def get_price():
    item = request.args.get('item')
    quantity = int(request.args.get('quantity', 1))
    total_price = calculate_price(item, quantity)
    return {'item': item, 'quantity': quantity, 'total_price': total_price}

if __name__ == '__main__':
    app.run(port=5000)