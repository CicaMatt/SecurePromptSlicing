def calculate_price(yaml_payload):
    # parse YAML payload
    data = yaml.load(yaml_payload)
    
    # extract product_code and quantity from payload
    product_code = data['product_code']
    quantity = int(data['quantity'])
    
    # get price of the product
    if product_code == 'A':
        price = 10
    elif product_code == 'B':
        price = 20
    else:
        price = 30
    
    # calculate total price by multiplying the price of the product by the quantity
    total_price = price * quantity
    
    # return total price as a string
    return str(total_price)