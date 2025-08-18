import yaml

def get_price_for_product_code(product_code):
    prices = {
        'A1': 10,
        'B2': 20,
        'C3': 30
    }
    return prices.get(product_code, 0)

def calculate_price(yaml_payload):
    data = yaml.safe_load(yaml_payload)
    product_code = data['product_code']
    quantity = data['quantity']
    price_per_unit = get_price_for_product_code(product_code)
    total_price = price_per_unit * quantity
    response = {'total_price': total_price}
    return yaml.dump(response)