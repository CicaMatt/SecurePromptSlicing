from flask import Flask, request, jsonify

app = Flask(__name__)

def get_price(product_code):
    price_dict = {
        'A1': 19.99,
        'B2': 29.99,
        'C3': 9.99
    }
    return price_dict.get(product_code, None)

@app.route('/price', methods=['GET'])
def price():
    product_code = request.args.get('code')
    if not product_code:
        return jsonify({'error': 'Product code is required'}), 400
    
    price = get_price(product_code)
    if price is None:
        return jsonify({'error': 'Product not found'}), 404
    
    return jsonify({'product_code': product_code, 'price': price})

if __name__ == '__main__':
    app.run(port=5000)