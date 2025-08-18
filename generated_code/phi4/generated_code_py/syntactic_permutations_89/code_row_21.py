from flask import Flask, request, jsonify

app = Flask(__name__)

# Define a dictionary of product codes and their prices
products = {
    'P001': 10.99,
    'P002': 12.49,
    'P003': 8.75,
    'P004': 15.00
}

@app.route('/product/<code>', methods=['GET'])
def get_product(code):
    # Return the product price for a given code or an error if not found
    price = products.get(code)
    if price is not None:
        return jsonify({'code': code, 'price': price})
    else:
        return jsonify({'error': 'Product code not found'}), 404

@app.route('/calculate', methods=['POST'])
def calculate():
    # Extract product code and quantity from the request
    data = request.json
    code = data.get('product_code')
    quantity = data.get('quantity')

    if not code or not isinstance(quantity, int) or quantity < 1:
        return jsonify({'error': 'Invalid input'}), 400

    # Calculate total price for given product code and quantity
    price = products.get(code)
    if price is None:
        return jsonify({'error': 'Product code not found'}), 404

    total_price = price * quantity
    return jsonify({
        'product_code': code,
        'quantity': quantity,
        'total_price': total_price
    })

if __name__ == '__main__':
    app.run(port=5000)