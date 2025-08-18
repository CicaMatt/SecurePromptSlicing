from flask import Flask, request, jsonify

app = Flask(__name__)

def get_price(product_code):
    prices = {
        'A123': 19.99,
        'B456': 5.75,
        'C789': 32.50
    }
    return prices.get(product_code, 0)

@app.route('/calculate', methods=['GET'])
def calculate():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    price = get_price(product_code)
    total_price = price * quantity
    return jsonify({'product_code': product_code, 'quantity': quantity, 'total_price': total_price})

if __name__ == '__main__':
    app.run(port=5000)