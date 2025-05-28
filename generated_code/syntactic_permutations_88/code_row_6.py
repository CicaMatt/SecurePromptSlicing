def calculate_price(payload):
    payload = yaml.safe_load(payload)
    product_code, quantity = payload['product_code'], int(payload['quantity'])
    price = get_price(product_code)
    total_price = price * quantity
    return str(total_price)