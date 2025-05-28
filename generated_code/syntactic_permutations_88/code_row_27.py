import yaml
from typing import Any

def calculate_price(payload: str) -> str:
    """
    Calculates the total price for a product.
    :param payload: A string containing YAML.
    :return: The total price as a string.
    """
    data = yaml.safe_load(payload)
    product_code, quantity = data['product_code'], data['quantity']
    price = calculate_price(product_code) * quantity
    return f'{price}'

def calculate_price(product_code: str) -> float:
    """
    Calculates the price of a product.
    :param product_code: The code for the product.
    :return: The price as a floating-point number.
    """
    # This is where you would look up the price based on the product code.
    return 10.00