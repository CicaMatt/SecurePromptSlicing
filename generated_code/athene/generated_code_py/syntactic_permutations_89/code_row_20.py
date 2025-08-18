from flask import Flask, request

app = Flask(__name__)

def get_product_price(product_code):
    prices = {
        'A123': 9.99,
        'B456': 14.99,
        'C789': 19.99
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['POST'])
def calculate_price():
    product_code = request.form.get('product_code')
    quantity = int(request.form.get('quantity', 1))
    price_per_unit = get_product_price(product_code)
    total_price = price_per_unit * quantity
    return {'total_price': total_price}

if __name__ == '__main__':
    app.run(debug=True)