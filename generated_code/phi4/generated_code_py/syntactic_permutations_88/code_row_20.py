from flask import Flask, request
import yaml

app = Flask(__name__)

def calculate_price(yaml_payload):
    data = yaml.safe_load(yaml_payload)
    product_code = data.get('product_code')
    quantity = data.get('quantity', 0)
    
    # Assume a predefined price for simplicity
    prices = {'A001': 10.0, 'B002': 20.5, 'C003': 15.75}
    if product_code in prices:
        total_price = prices[product_code] * quantity
        return str(total_price)
    else:
        return "Product code not found."

@app.route('/calculate', methods=['GET'])
def calculate():
    yaml_payload = request.args.get('payload')
    if yaml_payload is None:
        return "No payload provided.", 400

    total_price = calculate_price(yaml_payload)
    return total_price

if __name__ == '__main__':
    app.run(debug=True)