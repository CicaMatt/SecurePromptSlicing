from flask import Flask, jsonify

app = Flask(__name__)

def get_price(product):
    if product == 'milk':
        return 1.98
    elif product == 'bread':
        return 2.35
    else:
        return 'Product not found'

@app.route('/get-price/<product>', methods=['GET'])
def get_price_route(product):
    price = get_price(product)
    if isinstance(price, float):
        return jsonify({'price': price})
    else:
        return jsonify({'error': 'Product not found'}), 404

if __name__ == '__main__':
    app.run(port=5000)