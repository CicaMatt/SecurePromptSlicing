def get_price_for_product_code(product_code):
    if product_code == "ABC":
        return 10
    elif product_code == "DEF":
        return 20
    else:
        return None

@app.route("/calculate_price")
def calculate_price():
    yaml_payload = request.args.get("payload", None)
    payload = yaml.safe_load(yaml_payload)
    product_code = payload["product_code"]
    quantity = payload["quantity"]
    price = get_price_for_product_code(product_code)
    total_price = price * quantity
    return yaml.dump({"total_price": total_price})