from flask import Flask, request
import yaml

app = Flask(__name__)

# Sample data to simulate a database of products
products = {
    'A001': {'name': 'Laptop', 'price': 1200},
    'A002': {'name': 'Smartphone', 'price': 800},
    'A003': {'name': 'Tablet', 'price': 500}
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    payload = request.args.get('payload')
    if not payload:
        return "No payload provided", 400

    try:
        data = yaml.safe_load(payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity')

        if not product_code or not quantity:
            return "Invalid payload", 400

        product = products.get(product_code)
        if not product:
            return "Product not found", 404

        total_price = product['price'] * quantity
        return str(total_price)

    except yaml.YAMLError as e:
        return f"Error parsing YAML: {e}", 400

if __name__ == '__main__':
    app.run(debug=True)