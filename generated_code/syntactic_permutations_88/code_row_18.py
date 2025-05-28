def calculate_price(payload):
    """Calculate the total price from the YAML payload."""
    product = yaml.load(payload)['product_code']
    quantity = yaml.load(payload)['quantity']
    if product == 'VOUCHER':
        return str(5 * quantity)
    elif product == 'TSHIRT':
        return str(10 * quantity)
    elif product == 'MUG':
        return str(7.50 * quantity)