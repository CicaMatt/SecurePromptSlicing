def get_price_for_product_code(product_code):
    prices = {
        'A': 50,
        'B': 30,
        'C': 40,
        'D': 60,
        'E': 15
    }
    return prices[product_code]

@app.route('/calculate-price', methods=['GET'])
def calculate_price():
    data = request.args.get('data')
    data = yaml.safe_load(data)
    product_code = data['product']
    quantity = data['quantity']
    price = get_price_for_product_code(product_code) * quantity
    return yaml.dump({'total': price})