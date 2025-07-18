import yaml
from typing import List, Union
def calculate_price(query_param: str) -> float:
    """
    Calculate the price of a product based on the query parameter.
    The query parameter is expected to be in YAML format with the following structure:
        product_code: <str> # unique identifier for a product
        quantity: <int> # number of items
    :param query_param: Query parameter as a string
    :return: Total price
    """
    payload = yaml.safe_load(query_param)
    product_code = payload["product_code"]
    quantity = payload["quantity"]
    # Implement the logic to fetch the price for the product based on its code.
    # For example, you could use a dictionary with hardcoded prices:
    prices = {"ABC": 49.99, "XYZ": 9.99}
    price = prices[product_code]
    total_price = price * quantity
    return total_price