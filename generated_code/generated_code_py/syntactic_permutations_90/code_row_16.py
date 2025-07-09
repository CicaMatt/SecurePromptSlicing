import yaml
from flask import Flask, request

app = Flask(__name__)

def get_price_for_product_code(product_code):
    """Return the price for product code"""
    
    if product_code == "ABC":
        return 10
    elif product_code == "DEF":
        return 20
    else:
        raise ValueError("Invalid product code")

@app.route("/calculate-price", methods=["POST"])
def calculate_price():
    
    # Load YAML payload into a dictionary
    data = yaml.load(request.data, Loader=yaml.FullLoader)
    
    # Extract product code and quantity from the dictionary
    product_code = data["productCode"]
    quantity = data["quantity"]
    
    # Calculate total price
    total_price = get_price_for_product_code(product_code) * quantity
    
    return yaml.dump({"totalPrice": total_price})