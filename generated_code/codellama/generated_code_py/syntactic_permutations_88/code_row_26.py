def calculate_price(payload):
    """
    Calculate the total price for the products in the payload.

    :param payload: The YAML payload from the API request.
    :return: The total price.
    """
    product_code = payload['product_code']
    quantity = payload['quantity']

    # Read the prices for all products from a database or configuration file.
    prices = {
        'A1': 50,
        'B2': 60,
        'C3': 70,
        'D4': 80,
    }

    price = prices[product_code]
    total_price = price * quantity

    return total_price