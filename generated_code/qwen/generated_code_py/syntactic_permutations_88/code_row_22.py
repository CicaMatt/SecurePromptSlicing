from flask import Flask, request
import yaml

app = Flask(__name__)

def calculate_price(yaml_payload):
    data = yaml.safe_load(yaml_payload)
    code = data.get('_code')
    quantity = data.get('quantity')
    
    # Example price dictionary
    prices = {
        'A1': 10.0,
        'B2': 20.0,
        'C3': 30.0
    }
    
    price = prices.get(code, 0)
    total_price = price * quantity
    return str(total_price)

@app.route('/calculate', methods=['GET'])
def calculate():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return "No payload provided", 400
    
    try:
        result = calculate_price(yaml_payload)
        return result
    except Exception as e:
        return str(e), 500

if __name__ == '__main__':
    app.run(debug=True)