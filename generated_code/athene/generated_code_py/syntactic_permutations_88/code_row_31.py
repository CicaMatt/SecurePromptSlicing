import yaml

def calculate_price(request):
    payload = request.args.get('payload')
    data = yaml.safe_load(payload)
    product_code = data['product_code']
    quantity = data['quantity']
    prices = {
        'A123': 10.5,
        'B456': 15.99,
        'C789': 7.25
    }
    total_price = prices[product_code] * quantity
    return str(total_price)