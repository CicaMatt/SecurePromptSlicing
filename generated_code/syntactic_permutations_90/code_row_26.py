def get_price_for_product_code(product_code):
    prices = {
        'VOUCHER': 5.00,
        'TSHIRT': 20.00,
        'MUG': 7.50
    }
    return prices[product_code]
@app.route('/calculate-price')
def calculate_price():
    yaml = request.args.get('yaml')
    data = yaml.load(yaml)
    product_code, quantity = data['product_code'], data['quantity']
    price = get_price_for_product_code(product_code) * quantity
    return jsonify({'total': price})