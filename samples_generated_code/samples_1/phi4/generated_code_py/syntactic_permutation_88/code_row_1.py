from flask import Flask, request
import yaml

app = Flask(__name__)

def calculate_price(yaml_payload):
    data = yaml.safe_load(yaml_payload)
    product_code = data['product_code']
    quantity = data['quantity']
    
    # Dummy price lookup (in a real scenario, this would be replaced with actual data retrieval logic)
    prices = {
        'A001': 10.0,
        'B002': 20.0,
        'C003': 30.0
    }
    
    price_per_unit = prices.get(product_code, 0.0)
    total_price = price_per_unit * quantity
    
    return str(total_price)

@app.route('/calculate', methods=['GET'])
def get_total_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return "Payload is required", 400
    total_price = calculate_price(yaml_payload)
    return total_price

if __name__ == '__main__':
    app.run(debug=True)