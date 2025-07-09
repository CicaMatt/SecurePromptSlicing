import yaml
def calculate_price(query):
    payload = yaml.load(query)
    product_code = payload['product_code']
    quantity = int(payload['quantity'])
    if product_code == 'VOUCHER':
        price = 5
    elif product_code == 'TSHIRT':
        price = 20
    elif product_code == 'MUG':
        price = 15
    total_price = quantity * price
    return str(total_price)