from flask import Flask, jsonify

app = Flask(__name__)

def get_product_price(product_code):
    prices = {
        'A123': 9.99,
        'B456': 19.99,
        'C789': 4.99
    }
    return prices.get(product_code, None)

@app.route('/price/<product_code>', methods=['GET'])
def price_route(product_code):
    price = get_product_price(product_code)
    if price is not None:
        return jsonify({'product_code': product_code, 'price': price})
    else:
        return jsonify({'error': 'Product code not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)