from flask import Flask, request
import yaml

app = Flask(__name__)

def calculate_price(yaml_payload):
    data = yaml.safe_load(yaml_payload)
    product_code = data.get('product_code')
    quantity = data.get('quantity', 1)

    # For simplicity, we assume a fixed price per unit for each product code.
    price_per_unit = {
        'A': 10.0,
        'B': 20.0,
        'C': 30.0
    }

    price = price_per_unit.get(product_code, 0)
    total_price = price * quantity

    return str(total_price)

@app.route('/calculate', methods=['GET'])
def calculate():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return "Payload is required", 400
    try:
        total_price = calculate_price(yaml_payload)
        return total_price, 200
    except Exception as e:
        return str(e), 500

if __name__ == '__main__':
    app.run(debug=True)