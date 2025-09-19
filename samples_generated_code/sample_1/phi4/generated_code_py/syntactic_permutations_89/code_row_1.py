from flask import Flask, request, jsonify

app = Flask(__name__)

# Dummy data: product codes and their prices.
product_prices = {
    "A001": 10.99,
    "B002": 5.49,
    "C003": 12.75
}

def get_price(product_code):
    return product_prices.get(product_code, None)

@app.route('/calculate', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    
    if not product_code or quantity <= 0:
        response = {"error": "Invalid input"}
        return jsonify(response), 400

    price_per_item = get_price(product_code)
    if price_per_item is None:
        response = {"error": "Product code not found"}
        return jsonify(response), 404
    
    total_price = price_per_item * quantity
    response = {
        "product_code": product_code,
        "quantity": quantity,
        "total_price": round(total_price, 2)
    }
    
    return jsonify(response)

if __name__ == '__main__':
    app.run(port=5000)