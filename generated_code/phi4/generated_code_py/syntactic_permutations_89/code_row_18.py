from flask import Flask, jsonify

app = Flask(__name__)

# Dictionary to store product codes and their prices
product_prices = {
    "P001": 19.99,
    "P002": 29.99,
    "P003": 39.99,
}

@app.route('/price/<code>', methods=['GET'])
def get_price(code):
    price = product_prices.get(code)
    if price is not None:
        return jsonify({"product_code": code, "price": price})
    else:
        return jsonify({"error": "Product code not found"}), 404

if __name__ == '__main__':
    app.run(debug=True)