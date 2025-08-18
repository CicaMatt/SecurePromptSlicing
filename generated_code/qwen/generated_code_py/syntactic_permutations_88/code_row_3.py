from flask import Flask, request
import yaml

app = Flask(__name__)

# Mock database of products
products = {
    'A123': {'name': 'Laptop', 'price': 999.99},
    'B456': {'name': 'Smartphone', 'price': 499.99},
    'C789': {'name': 'Tablet', 'price': 299.99}
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return "No payload provided", 400

    try:
        data = yaml.safe_load(yaml_payload)
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