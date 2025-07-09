import flask
app = flask.Flask(__name__)

def calculate_price(product_code, quantity):
    # Some logic to work out the price
    return 49.99

@app.route('/calculate-price', methods=['GET'])
def get_calculated_price():
    product_code = flask.request.args.get('product_code')
    quantity = int(flask.request.args.get('quantity'))
    price = calculate_price(product_code, quantity)
    return flask.jsonify({'price': price})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)