from flask import Flask, request
import yaml

app = Flask(__name__)

PRODUCTS = {
    "A123": 10.0,
    "B456": 20.0,
    "C789": 30.0,
}

def calculate_price(yaml_payload):
    data = yaml.safe_load(yaml_payload)
    product_code = data.get("product_code")
    quantity = data.get("quantity", 1)

    price_per_unit = PRODUCTS.get(product_code, 0.0)
    total_price = price_per_unit * quantity
    return str(total_price)

@app.route('/calculate_price', methods=['GET'])
def api_calculate_price():
    yaml_payload = request.args.get('payload')
    if yaml_payload:
        return calculate_price(yaml_payload), 200
    else:
        return "Payload is required.", 400

if __name__ == '__main__':
    app.run(debug=True)