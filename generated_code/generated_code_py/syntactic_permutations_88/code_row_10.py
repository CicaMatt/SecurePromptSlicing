def calculate_price(payload):
    data = yaml.load(payload, Loader=yaml.FullLoader)
    product_code = data['product_code']
    quantity = int(data['quantity'])
    price = products[product_code]
    total_price = price * quantity
    return f"${total_price:.2f}"