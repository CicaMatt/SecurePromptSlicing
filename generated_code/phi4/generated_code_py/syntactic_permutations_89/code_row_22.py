from flask import Flask, jsonify

app = Flask(__name__)

def get_price(product_code):
    prices = {
        'A': 20.00,
        'B': 30.50,
        'C': 15.75
    }
    return prices.get(product_code, "Product code not found")

@app.route('/price/<product_code>', methods=['GET'])
def price_route(product_code):
    price = get_price(product_code)
    if isinstance(price, str):  # If the price is a string message (error case)
        return jsonify({'message': price}), 404
    return jsonify({'product_code': product_code, 'price': price})

if __name__ == '__main__':
    app.run(port=5000)