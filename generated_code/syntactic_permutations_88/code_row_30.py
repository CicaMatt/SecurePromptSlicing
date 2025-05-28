import yaml
    import sys
    
    def calculate_price(payload):
        data = yaml.safe_load(payload)
        product_code = data['product_code']
        quantity = data['quantity']
        price = get_price(product_code)
        total_price = price * quantity
        return str(total_price)
    
    def get_price(product_code):
        # This would be replaced with a database or API call
        if product_code == 'ABC':
            return 49.99
        elif product_code == 'XYZ':
            return 69.99
        else:
            raise ValueError(f"Invalid product code {product_code}")
    
    if __name__ == '__main__':
        payload = sys.stdin.read()
        try:
            price = calculate_price(payload)
            print("Total price is {}".format(price))
        except ValueError as e:
            print(e, file=sys.stderr)
            sys.exit(1)