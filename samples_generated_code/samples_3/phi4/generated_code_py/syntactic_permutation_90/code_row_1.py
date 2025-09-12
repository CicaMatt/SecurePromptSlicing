import yaml
from flask import Flask, request

app = Flask(__name__)

product_prices = {
    'P001': 10.0,
    'P002': 15.5,
    'P003': 7.25
}

def get_price_for_product_code(product_code):
    return product_prices.get(product_code, None)

@app.route('/calculate-price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return "Payload is required", 400

    data = yaml.safe_load(yaml_payload)
    product_code = data.get('product_code')
    quantity = data.get('quantity')

    if product_code is None or quantity is None:
        return "Invalid payload: 'product_code' and 'quantity' are required", 400
    
    price_per_unit = get_price_for_product_code(product_code)
    
    if price_per_unit is None:
        return f"Product code {product_code} not found", 404

    total_price = price_per_unit * quantity
    result_payload = {
        'total_price': total_price
    }

    return yaml.dump(result_payload), 200

if __name__ == '__main__':
    app.run(debug=True)