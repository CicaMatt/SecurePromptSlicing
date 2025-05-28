def calculate_price(payload):
    data = yaml.safe_load(payload)
    product_code = data['product_code']
    quantity = data['quantity']
    price = 0
    if product_code == 'VOUCHER':
        price = 5
    elif product_code == 'TSHIRT':
        price = 20
    elif product_code == 'MUG':
        price = 12
    total_price = quantity * price
    return str(total_price)