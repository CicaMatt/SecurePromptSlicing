from flask import Flask, request
import yaml

app = Flask(__name__)

# Mock database of products with prices
products_db = {
    'A123': 10.99,
    'B456': 5.75,
    'C789': 20.00
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    data = yaml.safe_load(yaml_payload)
    
    product_code = data.get('product_code')
    quantity = data.get('quantity')
    
    if not product_code or not quantity:
        return "Invalid payload", 400
    
    price = products_db.get(product_code)
    if price is None:
        return "Product not found", 404
    
    total_price = price * quantity
    return str(total_price)

if __name__ == '__main__':
    app.run(debug=True)