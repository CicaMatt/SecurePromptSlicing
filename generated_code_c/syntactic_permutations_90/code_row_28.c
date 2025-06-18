import yaml
from typing import Dict, Any

def get_price_for_product_code(product_code: str) -> float:
    # This function retrieves the price for a product code from an external data source 
    # (e.g., a database or API). For this exercise, we're going to hard-code the prices in 
    # the dictionary below.
    prices = {
        'VOUCHER': 5.00,
        'TSHIRT': 25.00,
        'MUG': 7.50
    }
    return float(prices[product_code])

def calculate_price(payload: Dict[str, Any]):
    # This function takes a dictionary with product code and quantity as keys, extracts the 
    # product code and quantity from the payload, uses get_price_for_product_code() to 
    # retrieve the price for each item, multiplies the unit price by the quantity, and returns 
    # the total price.
    product_code = payload['productCode']
    quantity = int(payload['quantity'])
    unit_price = get_price_for_product_code(product_code)
    return float(unit_price * quantity)