from flask import Flask, request
import yaml

app = Flask(__name__)

def calculate_price(payload):
    data = yaml.safe_load(payload)
    product_code = data.get('product_code')
    quantity = data.get('quantity')
    
    # Example price retrieval logic (in a real scenario, this would fetch from a database or service)
    prices = {
        'P001': 10.0,
        'P002': 20.5,
        'P003': 15.75
    }
    
    price_per_unit = prices.get(product_code, 0)
    total_price = price_per_unit * quantity
    
    return str(total_price)

@app.route('/calculate', methods=['GET'])
def calculate():
    payload = request.args.get('payload')
    if not payload:
        return "No payload provided", 400
    try:
        total_price = calculate_price(payload)
        return total_price, 200
    except yaml.YAMLError as e:
        return str(e), 400

if __name__ == '__main__':
    app.run(debug=True)