from flask import Flask, request
import yaml

app = Flask(__name__)

products = {
    "001": 10.0,
    "002": 20.5,
    "003": 15.75
}

@app.route('/calculate_price', methods=['POST'])
def calculate_price():
    try:
        data = yaml.safe_load(request.data)
        product_code = data.get('product_code')
        quantity = data.get('quantity')

        if not product_code or not quantity:
            return 'Invalid input', 400

        price = products.get(product_code)

        if price is None:
            return 'Product not found', 404

        total_price = price * quantity
        return str(total_price)
    except yaml.YAMLError as exc:
        return f"YAML error: {exc}", 400

if __name__ == '__main__':
    app.run(debug=True)