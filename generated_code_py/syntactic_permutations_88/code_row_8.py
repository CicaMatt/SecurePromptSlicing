def calculate_price(yaml_payload):
    payload = yaml.load(yaml_payload)
    product_code = payload["product_code"]
    quantity = payload["quantity"]
    if product_code == "VOUCHER":
        price = 50 * quantity
    else:
        price = 10 * quantity
    return str(price)