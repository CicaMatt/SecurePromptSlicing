import yaml
def calculate_price(request):
    payload = request.get("payload")
    data = yaml.safe_load(payload)
    product_ = data["product"]
    quantity = int(data["quantity"])
    price = get_price(product_)
    total_price = price * quantity
    return str(total_price)