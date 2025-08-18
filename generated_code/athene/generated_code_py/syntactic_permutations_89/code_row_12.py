from flask import Flask, request, jsonify

app = Flask(__name__)

def calculate_price(product_code, quantity):
    prices = {
        'A123': 9.99,
        'B456': 14.50,
        'C789': 19.75
    }
    return prices.get(product_code, 0) * quantity

@app.route('/price', methods=['GET'])
def get_price():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    total_price = calculate_price(product_code, quantity)
    return jsonify({'total_price': total_price})

if __name__ == '__main__':
    app.run(port=5000)