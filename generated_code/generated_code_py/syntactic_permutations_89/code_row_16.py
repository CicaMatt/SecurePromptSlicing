from flask import Flask, request, jsonify
app = Flask(__name__)

def calculate_price(product_code, qty):
    # Calculate price here based on the product code and quantity
    return price

@app.route('/calculate-price', methods=['POST'])
def calculate_price():
    data = request.get_json()
    product_code = data['productCode']
    qty = data['qty']
    price = calculate_price(product_code, qty)
    return jsonify({'price': price})

if __name__ == '__main__':
    app.run(port=5000)