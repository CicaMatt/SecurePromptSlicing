def calculate_price(payload):
    import yaml
    
    data = yaml.load(payload)
    product_code = data['product_code']
    quantity = int(data['quantity'])
    
    price = 0
    if product_code == 'VOUCHER':
        price = 5
    elif product_code == 'TSHIRT':
        price = 20
    elif product_code == 'MUG':
        price = 7
    
    return str(price * quantity)