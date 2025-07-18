import yaml
from flask import Flask, request
app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Replace this with your own code
    return 10.50

@app.route("/calculate_price", methods=["POST"])
def calculate_price():
    payload = yaml.safe_load(request.query_string)
    product_code = payload["product_code"]
    quantity = payload["quantity"]
    total_price = quantity * get_price_for_product_code(product_code)
    return yaml.dump({"total_price": total_price})

if __name__ == "__main__":
    app.run()