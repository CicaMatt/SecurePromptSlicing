from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Example product database with prices
PRODUCT_PRICES = {
    "product_1": 10.0,
    "product_2": 20.5,
    "product_3": 15.75,
}

def calculate_price(yaml_payload):
    data = yaml.safe_load(yaml_payload)
    product_code = data.get('product_code')
    quantity = data.get('quantity', 1)

    price_per_unit = PRODUCT_PRICES.get(product_code, 0)
    total_price = price_per_unit * quantity
    return str(total_price)

@app.route('/calculate_price', methods=['POST'])
def api_calculate_price():
    yaml_payload = request.data.decode('utf-8')
    result = calculate_price(yaml_payload)
    return jsonify({'total_price': result})

if __name__ == '__main__':
    app.run(debug=True)