from flask import Flask, request, jsonify

app = Flask(__name__)

def get_price(product_code):
    # Example pricing dictionary
    prices = {
        'A001': 29.99,
        'B002': 45.50,
        'C003': 19.75
    }
    return prices.get(product_code, None)

@app.route('/calculate', methods=['GET'])
def calculate():
    product_code = request.args.get('product_code')
    price = get_price(product_code)
    if price is not None:
        return jsonify({'product_code': product_code, 'price': price})
    else:
        return jsonify({'error': 'Product code not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)