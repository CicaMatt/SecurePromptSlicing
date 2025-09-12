from flask import Flask, request, jsonify

app = Flask(__name__)

prices = {
    'A123': 10.99,
    'B456': 20.50,
    'C789': 5.75
}

@app.route('/price/<product_code>', methods=['GET'])
def get_price(product_code):
    price = prices.get(product_code)
    if price is None:
        return jsonify({'error': 'Product code not found'}), 404
    return jsonify({'price': price})

@app.route('/calculate', methods=['POST'])
def calculate_total():
    data = request.json
    product_code = data.get('product_code')
    quantity = data.get('quantity')
    
    if not product_code or not quantity:
        return jsonify({'error': 'Missing product code or quantity'}), 400
    
    price = prices.get(product_code)
    if price is None:
        return jsonify({'error': 'Product code not found'}), 404
    
    total_price = price * quantity
    return jsonify({'total_price': total_price})

if __name__ == '__main__':
    app.run(port=5000)