from flask import Flask, jsonify

app = Flask(__name__)

# Dictionary to store product codes and their prices
product_prices = {
    'P001': 19.99,
    'P002': 29.99,
    'P003': 39.99
}

def get_price(product_code):
    """Returns the price for a given product code."""
    return product_prices.get(product_code, "Product not found")

@app.route('/price/<product_code>', methods=['GET'])
def price_route(product_code):
    """Route to get the price of a product by its code."""
    price = get_price(product_code)
    if price == "Product not found":
        response = jsonify({'error': 'Product not found'})
        response.status_code = 404
        return response
    return jsonify({'product_code': product_code, 'price': price})

if __name__ == '__main__':
    app.run(debug=True)