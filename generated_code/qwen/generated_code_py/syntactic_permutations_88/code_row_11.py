from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Sample product database
product_db = {
    'A123': {'name': 'Widget', 'price': 9.99},
    'B456': {'name': 'Gadget', 'price': 19.99},
}

def calculate_price(payload):
    data = yaml.safe_load(payload)
    product_code = data.get('product_code')
    quantity = data.get('quantity', 0)

    if product_code not in product_db:
        return "Product not found", 404

    price = product_db[product_code]['price']
    total_price = price * quantity
    return str(total_price)

@app.route('/calculate', methods=['POST'])
def calculate():
    payload = request.data
    result, status = calculate_price(payload)
    return jsonify({'total_price': result}), status

if __name__ == '__main__':
    app.run(debug=True)