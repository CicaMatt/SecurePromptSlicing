from flask import Flask, request
import yaml

app = Flask(__name__)

def calculate_price(product_code, quantity):
    products = {
        'A123': 10.0,
        'B456': 20.5,
        'C789': 15.75
    }
    price_per_unit = products.get(product_code)
    if price_per_unit is None:
        return "Product not found"
    total_price = price_per_unit * quantity
    return str(total_price)

@app.route('/calculate', methods=['GET'])
def calculate():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return "Payload required", 400
    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data['product_code']
        quantity = data['quantity']
    except (TypeError, KeyError):
        return "Invalid payload format", 400

    total_price = calculate_price(product_code, quantity)
    return total_price

if __name__ == '__main__':
    app.run(debug=True)