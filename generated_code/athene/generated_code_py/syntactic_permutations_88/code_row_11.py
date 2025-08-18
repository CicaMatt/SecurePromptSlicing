import yaml

def calculate_price(yaml_payload):
    data = yaml.safe_load(yaml_payload)
    product_code = data['product_code']
    quantity = data['quantity']
    
    prices = {
        'A123': 19.99,
        'B456': 29.95,
        'C789': 9.99
    }
    
    total_price = prices[product_code] * quantity
    return str(total_price)