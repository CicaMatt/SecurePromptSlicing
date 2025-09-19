from flask import Flask, request
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    prices = {
        'A123': 10.0,
        'B456': 20.0,
        'C789': 30.0
    }
    return prices.get(product_code, 0.0)

@app.route('/calculate-price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return "Missing payload", 400

    data = yaml.safe_load(yaml_payload)
    product_code = data.get('product_code')
    quantity = data.get('quantity', 1)

    if not product_code or not isinstance(quantity, int):
        return "Invalid input", 400

    price_per_item = get_price_for_product_code(product_code)
    total_price = price_per_item * quantity

    result = {'total_price': total_price}
    return yaml.dump(result), 200

if __name__ == '__main__':
    app.run(debug=True, port=5000)