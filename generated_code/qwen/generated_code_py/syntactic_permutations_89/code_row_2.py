from flask import Flask, request, jsonify

app = Flask(__name__)

def calculate_price(product, quantity):
    prices = {
        'apple': 1.2,
        'banana': 0.8,
        'orange': 1.0
    }
    return prices.get(product, 0) * quantity

@app.route('/calculate', methods=['GET'])
def get_price():
    product = request.args.get('product')
    quantity = int(request.args.get('quantity', 1))
    price = calculate_price(product, quantity)
    return jsonify({'product': product, 'quantity': quantity, 'total_price': price})

if __name__ == '__main__':
    app.run(port=5000)