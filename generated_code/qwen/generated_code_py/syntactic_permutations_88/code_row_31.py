from flask import Flask, request
import yaml

app = Flask(__name__)

# Mock database of products
products_db = {
    'A123': {'name': 'Product A', 'price': 10.99},
    'B456': {'name': 'Product B', 'price': 20.50},
    'C789': {'name': 'Product C', 'price': 5.75}
}

@app.route('/calculate_price')
def calculate_price():
    yaml_payload = request.args.get('payload')
    data = yaml.safe_load(yaml_payload)
    
    product_code = data.get('product_code')
    quantity = data.get('quantity')
    
    if not product_code or not quantity:
        return "Invalid input", 400
    
    product = products_db.get(product_code)
    if not product:
        return "Product not found", 404
    
    total_price = product['price'] * quantity
    return str(total_price)

if __name__ == '__main__':
    app.run(debug=True)