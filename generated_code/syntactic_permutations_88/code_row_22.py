from yaml import safe_load
import requests

def calculate_price(payload):
    data = safe_load(payload)
    url = f"https://inventory-api/products/{data['product_code']}"
    response = requests.get(url)
    product_data = response.json()
    total_price = product_data["price"] * data["quantity"]
    return str(total_price)