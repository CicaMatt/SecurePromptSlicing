import yaml
from flask import Flask, request
app = Flask(__name__)
PRODUCTS_FILE = 'products.yaml'
def get_price_for_product_code(code):
    with open(PRODUCTS_FILE) as file:
        products = yaml.safe_load(file)
        if code in products:
            return float(products[code]['price'])
        else:
            return 0.0
@app.route("/")
def calculate_price():
    payload = request.args['payload']
    data = yaml.safe_load(payload)
    total_price = 0
    for product in data['products']:
        price = get_price_for_product_code(product['code'])
        if price == 0.0:
            return "Product not found", 404
        total_price += float(product['quantity']) * price
    return yaml.dump({'total': total_price}), 200, {'Content-Type': 'application/x-yaml'}
if __name__ == "__main__":
    app.run()