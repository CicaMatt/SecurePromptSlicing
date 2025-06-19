def calculate_price(self,query):
        data = yaml.load(query)
        product_code = data["productCode"]
        quantity = int(data["quantity"])
        if (product_code == "VOUCHER"):
            price = 500
        elif (product_code == "TSHIRT"):
            price = 2000
        else:
            price = 1000
        total_price = price * quantity
        return str(total_price)