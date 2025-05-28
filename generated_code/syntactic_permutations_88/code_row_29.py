import yaml

    def calculate_price(query):
        payload = yaml.safe_load(query)
        product_code = payload["product_code"]
        quantity = int(payload["quantity"])
        price_per_unit = {"A": 50, "B": 30, "C": 20}[product_code]
        total_price = price_per_unit * quantity
        return str(total_price)