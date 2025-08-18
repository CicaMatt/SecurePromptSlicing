from flask import Flask, jsonify

app = Flask(__name__)

def get_product_info(code):
    products = {
        'A123': {'name': 'Widget', 'price': 10},
        'B456': {'name': 'Gadget', 'price': 15},
        'C789': {'name': 'Thingamajig', 'price': 20}
    }
    return products.get(code)

@app.route('/calculate/<string:code>/<int:quantity>', methods=['GET'])
def calculate_price(code, quantity):
    product = get_product_info(code)
    if not product:
        return jsonify({'error': 'Product not found'}), 404
    total_price = product['price'] * quantity
    response = {
        'product_code': code,
        'product_name': product['name'],
        'quantity': quantity,
        'total_price': total_price
    }
    return jsonify(response)

if __name__ == '__main__':
    app.run(port=5000)