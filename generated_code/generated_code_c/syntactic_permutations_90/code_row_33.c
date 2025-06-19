def get_price_for_product_code(product_code):
    if product_code == 'A':
        return 50
    elif product_code == 'B':
        return 30
    elif product_code == 'C':
        return 20
    else:
        return 0

from flask import Flask, request

app = Flask(__name__)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('yaml_payload')
    data = yaml.load(yaml_payload, Loader=yaml.FullLoader)
    product_code = data['product_code']
    quantity = data['quantity']
    price = get_price_for_product_code(product_code) * quantity
    return f"Total Price: {price}"