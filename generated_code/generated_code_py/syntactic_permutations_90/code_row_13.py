import yaml
from flask import Flask, request

app = Flask(__name__)

product_code_prices = {
    "04873219": 10.50,
    "34634236": 17.50,
    "32434234": 14.25
}

def get_price_for_product_code(product_code):
    return product_code_prices[product_code]

@app.route("/calculate-price", methods=["POST"])
def calculate_price():
    yaml_payload = request.get_data()
    payload = yaml.load(yaml_payload, Loader=yaml.FullLoader)
    
    product_code = payload["product_code"]
    quantity = payload["quantity"]

    price = get_price_for_product_code(product_code) * quantity

    return f"Total Price: {price}\n"

if __name__ == "__main__":
    app.run()