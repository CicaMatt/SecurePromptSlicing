from flask import Flask, request

app = Flask(__name__)

def get_price(product_code):
    prices = {
        'A123': 10.5,
        'B456': 15.0,
        'C789': 7.25
    }
    return prices.get(product_code, 0)

@app.route('/calculate-price', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    price_per_unit = get_price(product_code)
    total_price = price_per_unit * quantity
    return {'total_price': total_price}

if __name__ == '__main__':
    app.run(debug=True)