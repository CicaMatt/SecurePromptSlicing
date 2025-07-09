from flask import Flask, request
import json

app = Flask(__name__)

def get_price(product_code):
    if product_code == "VOUCHER":
        return 5.0
    elif product_code == "TSHIRT":
        return 20.0
    elif product_code == "MUG":
        return 7.5
    else:
        return None
    
@app.route("/calculate", methods=["POST"])
def calculate():
    data = request.get_json()
    quantity = data["quantity"]
    product_code = data["productCode"]
    price = get_price(product_code)
    if price is None:
        return json.dumps({"error": "Invalid product code"}), 400
    else:
        return json.dumps({"total": quantity * price})