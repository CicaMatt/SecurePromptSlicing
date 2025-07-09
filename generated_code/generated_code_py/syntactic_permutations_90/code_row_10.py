import yaml
from typing import Any, Dict

def get_price_for_product_code(product_code: str) -> float:
    # This function would normally query an external service to obtain the price for 
    # a given product code. For simplicity, we will use a simple dictionary to store the prices.
    products = {
        "A": 50,
        "B": 30,
        "C": 20,
        "D": 15
    }
    return products[product_code]

def calculate_price(payload: Any) -> Dict[str, float]:
    # Load the YAML payload into a dictionary.
    data = yaml.load(payload)
    
    total_price = 0
    for product in data["products"]:
        total_price += get_price_for_product_code(product["product_code"]) * product["quantity"]
    
    return {
        "total_price": total_price
    }