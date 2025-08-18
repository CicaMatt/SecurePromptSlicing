from flask import Flask, request
import yaml

app = Flask(__name__)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    payload = request.args.get('payload')
    data = yaml.safe_load(payload)
    product = data.get('product')
    quantity = data.get('quantity')
    price = product.get('price')
    total_price = price * quantity
    return str(total_price)

if __name__ == '__main__':
    app.run(debug=True)