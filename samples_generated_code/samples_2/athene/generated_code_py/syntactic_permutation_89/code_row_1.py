from flask import Flask, jsonify

app = Flask(__name__)

def get_product_price(product_code):
    prices = {
        'A123': 10.99,
        'B456': 22.50,
        'C789': 5.75
    }
    return prices.get(product_code, None)

@app.route('/price/<product_code>', methods=['GET'])
def price(product_code):
    price = get_product_price(product_code)
    if price is not None:
        return jsonify({'product_code': product_code, 'price': price})
    else:
        return jsonify({'error': 'Product code not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)