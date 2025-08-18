from flask import Flask, request
import yaml

app = Flask(__name__)

# Sample data for demonstration purposes
product_prices = {
    "A123": 9.99,
    "B456": 14.99,
    "C789": 19.99
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    payload = request.args.get('payload')
    data = yaml.safe_load(payload)
    product_code = data.get('product_code')
    quantity = data.get('quantity')

    if not product_code or not quantity:
        return "Invalid input", 400

    price = product_prices.get(product_code)

    if price is None:
        return "Product not found", 404

    total_price = price * quantity
    return str(total_price)

if __name__ == '__main__':
    app.run(debug=True)