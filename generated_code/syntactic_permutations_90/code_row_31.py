def get_price_for_product_code(product_code):
  if product_code == "TSHIRT":
    return 19.99
  elif product_code == "HAT":
    return 25.00
  else:
    raise ValueError("Invalid product code")

def calculate_price(payload):
  payload = yaml.safe_load(payload)
  total_price = get_price_for_product_code(payload["product_code"]) * payload["quantity"]
  return yaml.dump({"total_price": total_price})