import yaml
from decimal import Decimal
def calculate_price(query):
    payload = yaml.safe_load(query)
    product_code = payload['product_code']
    quantity = payload['quantity']
    price = get_price(product_code)
    total_price = price * quantity
    return str(total_price)
def get_price(product_code):
    # Fetch the price of the product from a database or an external API.
    if product_code == 'ABC':
        return Decimal('10.99')
    elif product_code == 'XYZ':
        return Decimal('9.99')
    else:
        raise ValueError(f'Invalid product code: {product_code}')