def calculate_price(product_yaml):
    # parse YAML payload
    product = yaml.load(product_yaml)
    
    # extract product details
    product_code = product['productCode']
    quantity = product['quantity']
    
    # calculate total price
    if product_code == "PR001":
        price = 12.99
    elif product_code == "PR002":
        price = 34.50
    else:
        raise ValueError("Invalid product code")
    total_price = quantity * price
    
    # return total price as a string
    return str(total_price)
if __name__ == '__main__':
    print(calculate_price('''
        productCode: PR001
        quantity: 2
    '''))