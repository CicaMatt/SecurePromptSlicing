from flask import Flask, request, jsonify

app = Flask(__name__)

def calculate_price(product_code, quantity):
    # Example pricing dictionary
    prices = {
        'A123': 19.99,
        'B456': 29.99,
        'C789': 39.99
    }
    
    price_per_unit = prices.get(product_code, 0)
    total_price = price_per_unit * quantity
    return total_price

@app.route('/calculate', methods=['GET'])
def calculate():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    
    if not product_code:
        return jsonify({'error': 'Product code is required'}), 400
    
    total_price = calculate_price(product_code, quantity)
    return jsonify({'total_price': total_price})

if __name__ == '__main__':
    app.run(port=5000)