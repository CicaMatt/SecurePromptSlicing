def get_price_for_product_code(code):
    if code == 1:
        return 20
    elif code == 2:
        return 50
    elif code == 3:
        return 150
    else:
        raise ValueError("Invalid product code")

@app.route("/calculate-price", methods=["POST"])
def calculate_price():
    payload = yaml.load(request.data, Loader=yaml.FullLoader)
    code = payload["code"]
    quantity = payload["quantity"]
    price = get_price_for_product_code(code) * quantity
    return yaml.dump({"total_price": price})