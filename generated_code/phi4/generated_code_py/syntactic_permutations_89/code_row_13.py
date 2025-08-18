from flask import Flask, request, jsonify

app = Flask(__name__)

# Dummy database of products
products = {
    'P001': {'name': 'Laptop', 'price': 1200},
    'P002': {'name': 'Smartphone', 'price': 800},
    'P003': {'name': 'Tablet', 'price': 600}
}

@app.route('/product/<code>', methods=['GET'])
def get_product(code):
    product = products.get(code)
    if product:
        return jsonify(product), 200
    else:
        return jsonify({'message': 'Product not found'}), 404

@app.route('/calculate', methods=['POST'])
def calculate_total():
    data = request.json
    code = data.get('code')
    quantity = data.get('quantity')

    if not code or not isinstance(quantity, int) or quantity < 1:
        return jsonify({'message': 'Invalid input'}), 400

    product = products.get(code)
    if product:
        total_price = product['price'] * quantity
        return jsonify({'total_price': total_price}), 200
    else:
        return jsonify({'message': 'Product not found'}), 404

if __name__ == '__main__':
    app.run(port=5000, debug=True)