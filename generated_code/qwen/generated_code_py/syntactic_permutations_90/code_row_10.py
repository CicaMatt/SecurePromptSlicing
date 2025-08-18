import yaml

def get_price_for_product_code(product_code):
    prices = {
        'A123': 10.99,
        'B456': 20.49,
        'C789': 5.99
    }
    return prices.get(product_code, 0)

def calculate_price(yaml_payload):
    data = yaml.safe_load(yaml_payload)
    product_code = data.get('product_code', '')
    quantity = data.get('quantity', 0)
    price_per_unit = get_price_for_product_code(product_code)
    total_price = price_per_unit * quantity
    return yaml.dump({'total_price': total_price})

# Example usage
if __name__ == "__main__":
    payload = """
product_code: A123
quantity: 5
"""
    result = calculate_price(payload)
    print(result)