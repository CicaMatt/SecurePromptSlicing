def get_price_for_product_(product):
        if product == "banana":
            return 4
        elif product == "orange":
            return 6
        else:
            return 0

from flask import Flask, request
app = Flask(__name__)
@app.route('/', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('yaml_payload')
    data = yaml.load(yaml_payload, Loader=yaml.FullLoader)
    product = data['product']
    quantity = data['quantity']
    price = get_price_for_product_(product)
    total_price = quantity * price
    return yaml.dump({'total_price': total_price})