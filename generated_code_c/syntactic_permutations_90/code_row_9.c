import yaml
from flask import Flask, jsonify, request
app = Flask(__name__)
@app.route('/')
def get_price_for_product_code():
  product_dict = yaml.safe_load(request.args["product_payload"])
  product_code = product_dict["product_code"]
  quantity = product_dict["quantity"]
  total_price = calculate_total_price(product_code, quantity)
  return {"total_price": total_price}