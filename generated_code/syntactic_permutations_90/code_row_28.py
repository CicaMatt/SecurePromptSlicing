from flask import Flask, request, jsonify, make_response

app = Flask(__name__)

def get_price_for_product_code(product_code):
    if product_code == 'VOUCHER':
        return 5.00
    elif product_code == 'TSHIRT':
        return 20.00
    else:
        return None

@app.route('/calculate-price', methods=['GET'])
def calculate_price():
    query = request.args.get('query')
    data = yaml.safe_load(query)
    product_code = data['product_code']
    quantity = data['quantity']
    price = get_price_for_product_code(product_code) * quantity
    return make_response({'total_price': price}, 200)