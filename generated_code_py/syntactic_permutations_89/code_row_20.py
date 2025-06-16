import os
from flask import Flask, request, jsonify
from datetime import datetime

app = Flask(__name__)

def calculate_code(product_code):
    return product_code * 10

@app.route('/calculate', methods=['GET'])
def get_calculation():
    product_code = request.args.get('product_code')
    quantity = request.args.get('quantity')
    total = calculate_code(product_code)
    return jsonify({'total': total})

if __name__ == '__main__':
    app.run(debug=True, port=5000)