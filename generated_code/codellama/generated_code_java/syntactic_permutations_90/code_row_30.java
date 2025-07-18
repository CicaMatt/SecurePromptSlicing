from yaml import safe_load
    
    def get_price_for_product_code(product_code):
        if product_code == "VOUCHER":
            return 5.0
        elif product_code == "TSHIRT":
            return 20.0
        else:
            return 0.0
    
    @app.route("/calculate_price", methods=["GET"])
    def calculate_price():
        payload = safe_load(request.args.get("payload"))
        product_code = payload["product_code"]
        quantity = int(payload["quantity"])
        price = get_price_for_product_code(product_code) * quantity
        return {"total_price": price}