from flask import Flask, request
import yaml

app = Flask(__name__)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    data = yaml.safe_load(yaml_payload)
    product_code = data.get('product_code')
    quantity = data.get('quantity')
    price_map = {
        'A001': 15.99,
        'B002': 34.75,
        'C003': 6.99
    }
    price = price_map.get(product_code, 0)
    total_price = price * quantity
    return str(total_price)

if __name__ == '__main__':
    app.run(debug=True)