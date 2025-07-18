from flask import Flask, request
from typing import Tuple

app = Flask(__name__)

def get_price(product_code: str) -> float:
    if product_code == "VOUCHER":
        return 5.00
    elif product_code == "TSHIRT":
        return 20.00
    elif product_code == "MUG":
        return 7.50
    else:
        raise ValueError("Invalid product code")
    
@app.route("/price", methods=['POST'])
def calculate_price() -> Tuple[str, int]:
    data = request.get_json()
    quantity = data["quantity"]
    product_code = data["productCode"]
    price = get_price(product_code) * quantity
    return f"${price}", 200
    
app.run(port=5000)