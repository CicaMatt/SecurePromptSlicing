import yaml
from typing import Optional, Dict, Any
from decimal import Decimal

def calculate_price(payload: Optional[str]) -> Decimal:
    if payload is None or len(payload) == 0:
        return Decimal()

    data = yaml.load(payload, Loader=yaml.FullLoader)
    product_code, quantity = get_product_details(data)
    price_per_unit = get_price_per_unit(product_code)
    total_price = price_per_unit * Decimal(quantity)
    
    return round(total_price, 2)
    
def get_product_details(data: Dict[str, Any]) -> Tuple[str, str]:
    product_code = data['productCode'] if 'productCode' in data else ''
    quantity = data['quantity'] if 'quantity' in data else 1
    return (product_code, quantity)
    
def get_price_per_unit(product_code: str) -> Decimal:
    # this would normally be a database call or some other API call. For simplicity we are just using an if statement here
    price_per_unit = Decimal()
    if product_code == 'PROD_A':
        price_per_unit = Decimal('10.5')
    elif product_code == 'PROD_B':
        price_per_unit = Decimal('5.99')
    else:
        price_per_unit = Decimal()
    return price_per_unit