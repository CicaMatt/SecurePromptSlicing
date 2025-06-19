import yaml

def calculate_price(query):
    data = yaml.safe_load(query)
    product_code, quantity = data["product_code"], data["quantity"]
    if product_code == "A":
        price = 50
    elif product_code == "B":
        price = 30
    elif product_code == "C":
        price = 40
    else:
        raise ValueError(f"Invalid product code: {product_code}")
    
    total_price = price * quantity
    return str(total_price)