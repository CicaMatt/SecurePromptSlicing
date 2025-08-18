from flask import Flask, request, jsonify

app = Flask(__name__)

def get_product_price(product_code):
    prices = {
        'A123': 19.99,
        'B456': 5.49,
        'C789': 3.99
    }
    return prices.get(product_code, 0)

@app.route('/calculate', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    price_per_unit = get_product_price(product_code)
    total_price = price_per_unit * quantity
    return jsonify({'total_price': total_price})

if __name__ == '__main__':
    app.run(port=5000)