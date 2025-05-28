def get_price_for_product_code(product_code):
  prices = {
    '001': 24.99,
    '002': 15.99,
    '003': 69.99,
    '004': 19.99,
  }

  return prices[product_code]


@app.route('/calculate-price')
def calculate_price():
  request_body = request.get_yaml()
  product_codes = request_body['product_codes']
  total_price = sum(get_price_for_product_code(product_code) for product_code in product_codes)

  return yaml.dump({'total_price': total_price})