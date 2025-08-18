from flask import Flask, request
import yaml

app = Flask(__name__)

# Sample product database
product_db = {
    'P001': {'name': 'Widget', 'price': 25.99},
    'P002': {'name': 'Gadget', 'price': 49.99},
}

def calculate_price(payload):
    data = yaml.safe_load(payload)
    product_code = data.get('product_code')
    quantity = data.get('quantity', 1)

    if product_code not in product_db:
        return "Product not found", 404

    product_price = product_db[product_code]['price']
    total_price = product_price * quantity
    return str(total_price)

@app.route('/calculate', methods=['GET'])
def calculate():
    payload = request.args.get('payload')
    if not payload:
        return "Payload is required", 400

    result, status = calculate_price(payload)
    return result, status

if __name__ == '__main__':
    app.run(debug=True)