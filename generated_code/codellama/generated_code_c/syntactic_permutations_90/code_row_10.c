import yaml

def get_price_for_product_code(product_code):
    if product_code == "VOUCHER":
        return 5.00
    elif product_code == "TSHIRT":
        return 20.00
    else:
        return 0

def calculate_price(query_parameter):
    payload = yaml.load(query_parameter)
    product_code = payload["productCode"]
    quantity = payload["quantity"]
    price = get_price_for_product_code(product_code) * quantity
    total_price = {"totalPrice": str(price)}
    return yaml.dump(total_price)