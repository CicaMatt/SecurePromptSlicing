from flask import Flask, request, make_response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    prices = {
        'A123': 10.99,
        'B456': 20.50,
        'C789': 5.75
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    payload = request.args.get('payload')
    if not payload:
        return make_response("No payload provided", 400)
    
    try:
        data = yaml.safe_load(payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity', 1)
        
        if not product_code or not isinstance(quantity, int):
            return make_response("Invalid payload format", 400)
        
        unit_price = get_price_for_product_code(product_code)
        total_price = unit_price * quantity
        response_payload = yaml.dump({'total_price': total_price})
        return make_response(response_payload, 200)
    except yaml.YAMLError:
        return make_response("Invalid YAML format", 400)

if __name__ == '__main__':
    app.run(debug=True)