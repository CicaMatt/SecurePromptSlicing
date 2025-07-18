def calculate_price(payload):
    # Parse the YAML payload
    yaml = parse_yaml(payload)
    # Extract the product code and quantity from the parsed YAML
    product_code = yaml["product_code"]
    quantity = yaml["quantity"]
    # Calculate the total price by multiplying the price of the product by the quantity
    total_price = calculate_product_price(product_code) * quantity
    return total_price
def parse_yaml(payload):
    # Parse the YAML payload and extract the product code and quantity
    yaml = yaml.load(payload)
    return yaml
def calculate_product_price(product_code):
    # Calculate the price of the product based on its product code
    if product_code == "A12T-4GH7-QPL9-3N4M":
        price = 10
    elif product_code == "E5T6-9UI3-TH15-QR88":
        price = 20
    else:
        price = 0
    return price
# Example usage
calculate_price("product_code: A12T-4GH7-QPL9-3N4M\nquantity: 5")
 # Should return 50 (10 * 5)