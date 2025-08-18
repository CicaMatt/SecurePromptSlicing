from flask import Flask, request, jsonify

app = Flask(__name__)

def calculate_price(product_code, quantity):
    # Example price dictionary for products
    prices = {
        'A123': 19.99,
        'B456': 5.75,
        'C789': 3.50
    }
    
    return prices.get(product_code, 0) * quantity

@app.route('/calculate', methods=['GET'])
def calculate():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    total_price = calculate_price(product_code, quantity)
    return jsonify({'product_code': product_code, 'quantity': quantity, 'total_price': total_price})

if __name__ == '__main__':
    app.run(port=5000)