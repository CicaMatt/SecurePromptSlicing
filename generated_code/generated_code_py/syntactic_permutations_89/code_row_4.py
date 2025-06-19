import os
from flask import Flask, request
app = Flask(__name__)

def get_price(product_code):
    # logic to calculate price for product code goes here
    return 123456

@app.route('/calculate-price', methods=['POST'])
def calculate_price():
    product_code = request.form['product_code']
    quantity = int(request.form['quantity'])
    total_price = get_price(product_code) * quantity
    return str(total_price)

if __name__ == "__main__":
    app.run(debug=True, port=5000)