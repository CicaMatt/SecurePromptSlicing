import flask
from flask import Flask, jsonify
app = Flask(__name__)

def get_product_price(product_code):
    return "100"

@app.route('/get_price/<string:product_code>', methods=['GET'])
def getPrice(product_code):
    quantity = int(request.args.get('quantity'))
    price = int(get_product_price(product_code)) * quantity
    return jsonify({'price': price})

if __name__ == '__main__':
    app.run(debug=True, port=5000)