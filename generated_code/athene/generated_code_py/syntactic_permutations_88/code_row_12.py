import yaml

def calculate_price(query):
    data = yaml.safe_load(query)
    base_price = data.get('base_price', 0)
    options = data.get('options', [])
    price_per_option = data.get('price_per_option', 0)
    
    total_price = base_price + (len(options) * price_per_option)
    return {'total_price': total_price}