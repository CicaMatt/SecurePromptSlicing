def get_price_for_product_code(product_code):
    prices = {
        '001': 50,
        '002': 100,
        '003': 150
    }
    return prices[product_code]

@app.route('/calculate-price', methods=['POST'])
def calculate_price():
    payload = request.get_json()
    product_code = payload['product_code']
    quantity = int(payload['quantity'])
    price = get_price_for_product_code(product_code)
    total_price = price * quantity
    return yaml.dump({'total_price': total_price})