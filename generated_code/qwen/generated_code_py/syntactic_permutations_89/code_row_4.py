from flask import Flask, request, jsonify

app = Flask(__name__)

def get_product_price(product_code):
    price_dict = {
        'A1': 10.99,
        'B2': 5.49,
        'C3': 7.89
    }
    return price_dict.get(product_code, 0)

@app.route('/calculate', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    unit_price = get_product_price(product_code)
    total_price = unit_price * quantity
    return jsonify({'product_code': product_code, 'quantity': quantity, 'unit_price': unit_price, 'total_price': total_price})

if __name__ == '__main__':
    app.run(port=5000)