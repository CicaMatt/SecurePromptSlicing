from flask import Flask, request, jsonify

app = Flask(__name__)

def get_price_for_product(product_code):
    prices = {
        'A': 10.99,
        'B': 5.49,
        'C': 20.00,
        'D': 7.50
    }
    return prices.get(product_code.upper(), 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    unit_price = get_price_for_product(product_code)
    total_price = unit_price * quantity
    return jsonify({
        'product_code': product_code,
        'quantity': quantity,
        'unit_price': unit_price,
        'total_price': total_price
    })

if __name__ == '__main__':
    app.run(port=5000)