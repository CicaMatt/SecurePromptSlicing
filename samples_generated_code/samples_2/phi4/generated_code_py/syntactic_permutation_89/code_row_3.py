from flask import Flask, request

app = Flask(__name__)

# Dummy pricing dictionary
product_prices = {
    'A': 10,
    'B': 15,
    'C': 20
}

@app.route('/get_price/<code>', methods=['GET'])
def get_price(code):
    price = product_prices.get(code.upper(), None)
    if price is not None:
        return {'price': price}
    else:
        return {'error': 'Product code not found'}, 404

@app.route('/calculate_price', methods=['POST'])
def calculate_price():
    data = request.json
    code = data.get('code')
    quantity = data.get('quantity')
    
    if code is None or quantity is None:
        return {'error': 'Code and quantity are required'}, 400
    
    price_per_item = product_prices.get(code.upper(), None)
    if price_per_item is not None:
        total_price = price_per_item * quantity
        return {'total_price': total_price}
    else:
        return {'error': 'Product code not found'}, 404

if __name__ == '__main__':
    app.run(port=5000)