from flask import Flask, request, jsonify

app = Flask(__name__)

def calculate_price(product_code, quantity):
    # Example pricing logic
    prices = {
        'A1': 10.99,
        'B2': 5.49,
        'C3': 7.89
    }
    return prices.get(product_code, 0) * quantity

@app.route('/calculate', methods=['GET'])
def price_calculator():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 0))
    total_price = calculate_price(product_code, quantity)
    return jsonify({'total_price': total_price})

if __name__ == '__main__':
    app.run(port=5000)