from flask import Flask, request, jsonify

app = Flask(__name__)

prices = {
    'A123': 10.5,
    'B456': 20.0,
    'C789': 15.75
}

def get_price(product_code):
    return prices.get(product_code, None)

@app.route('/calculate', methods=['GET'])
def calculate():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    
    price_per_unit = get_price(product_code)
    if price_per_unit is None:
        return jsonify({"error": "Product code not found"}), 404
    
    total_price = price_per_unit * quantity
    return jsonify({"total_price": total_price})

if __name__ == '__main__':
    app.run(port=5000)