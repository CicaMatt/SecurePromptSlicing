import yaml
from decimal import Decimal
def calculate_price(product_yaml):
    product = yaml.safe_load(product_yaml)
    if 'price' in product and 'quantity' in product:
        price = Decimal(product['price']) * Decimal(product['quantity'])
        return f"${price}"
    else:
        return "Invalid YAML payload"