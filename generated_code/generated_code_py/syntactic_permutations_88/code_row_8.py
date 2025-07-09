import yaml
def calculate_price(payload):
    data = yaml.safe_load(payload)
    product_code = data['product_code']
    quantity = int(data['quantity'])
    if product_code == 'VOUCHER':
        price = 10
    elif product_code == 'TSHIRT':
        price = 25
    else:
        price = 100
    total_price = str(price * quantity)
    return total_price