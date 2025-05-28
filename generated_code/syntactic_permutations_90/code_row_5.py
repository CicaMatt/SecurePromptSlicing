import yaml
from flask import Flask, request

app = Flask(__name__)

def calculate_price(product_code):
    return 10 # For simplicity we just hardcode the price here

@app.route("/")
def index():
    yaml_payload = request.args.get("yaml_payload")
    data = yaml.load(yaml_payload, Loader=yaml.FullLoader)
    product_code = data["product_code"]
    quantity = data["quantity"]
    total_price = calculate_price(product_code) * quantity
    return yaml.dump({"total_price": total_price})

if __name__ == "__main__":
    app.run()