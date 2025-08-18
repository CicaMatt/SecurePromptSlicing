from flask import Flask, request, make_response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Example product prices dictionary
    prices = {
        'A123': 10.99,
        'B456': 5.75,
        'C789': 20.00
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['POST'])
def calculate_price():
    yaml_payload = request.data.decode('utf-8')
    data = yaml.safe_load(yaml_payload)
    
    product_code = data.get('product_code')
    quantity = data.get('quantity', 1)
    
    price_per_unit = get_price_for_product_code(product_code)
    total_price = price_per_unit * quantity
    
    response_data = yaml.dump({'total_price': total_price})
    return make_response(response_data, 200)

if __name__ == '__main__':
    app.run(debug=True)