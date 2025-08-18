from flask import Flask, request, jsonify

app = Flask(__name__)

# Sample product prices dictionary
product_prices = {
    'P001': 10.99,
    'P002': 15.49,
    'P003': 7.89
}

def get_price(product_code):
    return product_prices.get(product_code, None)

@app.route('/calculate', methods=['GET'])
def calculate():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    
    price = get_price(product_code)
    if price is not None:
        total_price = price * quantity
        return jsonify({'total_price': total_price})
    else:
        return jsonify({'error': 'Invalid product code'}), 404

if __name__ == '__main__':
    app.run(port=5000)