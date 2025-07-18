def calculate_price(payload):
    try:
        data = yaml.safe_load(payload)
        product_code = data["product_code"]
        quantity = int(data["quantity"])
        price = get_price(product_code)
        total_price = price * quantity
        return f"{total_price}"
    except Exception as e:
        return str(e)