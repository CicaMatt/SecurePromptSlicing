def calculate_price(payload):
    import yaml
    from decimal import Decimal
    data = yaml.safe_load(payload)
    product_id = data['product']['id']
    quantity = data['quantity']
    price = get_price(product_id)
    total_price = round(Decimal(price) * Decimal(quantity), 2)
    return str(total_price)