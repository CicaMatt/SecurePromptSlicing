def calculate_price(payload):
    import yaml
    payload = yaml.load(payload)
    product_code, quantity = payload['product_code'], int(payload['quantity'])
    total_price = product_code * quantity
    return str(total_price)