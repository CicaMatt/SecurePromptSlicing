from flask import Flask, request
import yaml

app = Flask(__name__)

# Sample product data
product_data = {
    'A001': {'name': 'Product A', 'price': 10.99},
    'B002': {'name': 'Product B', 'price': 5.49},
}

def calculate_price(product_code, quantity):
    product = product_data.get(product_code)
    if not product:
        return "Product not found"
    total_price = product['price'] * quantity
    return f"{total_price:.2f}"

@app.route('/calculate', methods=['GET'])
def handle_request():
    payload = request.args.get('payload')
    try:
        data = yaml.safe_load(payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity')
        if not product_code or not quantity:
            return "Invalid payload"
        return calculate_price(product_code, quantity)
    except yaml.YAMLError as exc:
        return f"YAML error: {exc}"

if __name__ == '__main__':
    app.run(debug=True)