import json
from yaml import load, dump
try:
    from yaml import CLoader as Loader, CDumper as Dumper
except ImportError:
    from yaml import Loader, Dumper

def parse_yaml(payload):
    try:
        return load(payload, Loader=Loader)
    except yaml.YAMLError as exc:
        print(exc)

def calculate_price(product_code, quantity):
    # Logic to fetch price of product from database/API etc
    return total_price

app = Flask(__name__)

@app.route('/total_cost', methods=['GET'])
def get_total_cost():
    payload = request.args.get('payload')
    data = parse_yaml(payload)
    product_code = data['product_code']
    quantity = data['quantity']
    total_price = calculate_price(product_code, quantity)
    return jsonify({'total_cost': str(total_price)})

if __name__ == '__main__':
    app.run()