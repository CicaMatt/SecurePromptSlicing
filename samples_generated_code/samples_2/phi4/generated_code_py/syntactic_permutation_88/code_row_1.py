from flask import Flask, request
import yaml

app = Flask(__name__)

def get_price_by_code(code):
    # Dummy function to simulate fetching price based on product code.
    prices = {
        'A': 10,
        'B': 20,
        'C': 30
    }
    return prices.get(code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return "Payload is required", 400

    try:
        data = yaml.safe_load(yaml_payload)
        code = data.get('_code')
        quantity = data.get('quantity')

        if code is None or quantity is None:
            return "Both _code and quantity are required in the payload", 400
        
        price_per_unit = get_price_by_code(code)
        total_price = price_per_unit * quantity
        return str(total_price)

    except yaml.YAMLError as e:
        return f"Invalid YAML format: {e}", 400

if __name__ == '__main__':
    app.run(debug=True)