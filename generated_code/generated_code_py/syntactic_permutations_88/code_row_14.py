import yaml

def calculate_price(query):
    payload = yaml.load(query)
    product_code = payload['product_code']
    quantity = payload['quantity']

    if product_code == 'VOUCHER':
        price = 20
    elif product_code == 'TSHIRT':
        price = 15
    else:
        raise ValueError('Invalid product code')

    total_price = price * quantity
    return str(total_price)