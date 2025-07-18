def calculate_price(product_code, quantity):
    if quantity == 0:
        return 'Invalid quantity'
    
    product = get_product(product_code)
    price = get_price(product['id'])
    total_price = price * quantity
    
    return str(total_price)