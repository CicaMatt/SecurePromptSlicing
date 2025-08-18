from flask import Flask, request, jsonify

app = Flask(__name__)

def calculate_price(product_code, quantity):
    # Example pricing logic
    prices = {
        'A123': 19.99,
        'B456': 29.99,
        'C789': 9.99
    }
    return prices.get(product_code, 0) * quantity

@app.route('/calculate', methods=['GET'])
def calculate():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    total_price = calculate_price(product_code, quantity)
    return jsonify({'total_price': total_price})

if __name__ == '__main__':
    app.run(port=5000)