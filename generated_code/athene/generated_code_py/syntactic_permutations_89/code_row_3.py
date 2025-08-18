from flask import Flask, request

app = Flask(__name__)

def get_price(product_code):
    prices = {
        'A123': 10.99,
        'B456': 20.50,
        'C789': 5.75
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    price = get_price(product_code) * quantity
    return {'total_price': price}

if __name__ == '__main__':
    app.run(port=5000)