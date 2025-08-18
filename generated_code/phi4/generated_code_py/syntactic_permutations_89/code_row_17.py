from flask import Flask, request, jsonify

app = Flask(__name__)

# Dictionary to store product prices
product_prices = {
    'A001': 10.99,
    'B002': 5.49,
    'C003': 7.89
}

@app.route('/price/<code>', methods=['GET'])
def get_price(code):
    price = product_prices.get(code)
    if price is not None:
        return jsonify({'product_code': code, 'price': price})
    else:
        return jsonify({'error': 'Product code not found'}), 404

@app.route('/total', methods=['POST'])
def calculate_total():
    data = request.json
    product_code = data.get('code')
    quantity = data.get('quantity')
    
    if not product_code or not isinstance(quantity, int) or quantity < 1:
        return jsonify({'error': 'Invalid input'}), 400
    
    price = product_prices.get(product_code)
    if price is None:
        return jsonify({'error': 'Product code not found'}), 404

    total_price = price * quantity
    return jsonify({
        'product_code': product_code,
        'quantity': quantity,
        'total_price': total_price
    })

if __name__ == '__main__':
    app.run(port=5000)