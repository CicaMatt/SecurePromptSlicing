from flask import Flask, request
import yaml

app = Flask(__name__)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    
    # Parse YAML payload
    data = yaml.safe_load(yaml_payload)
    
    product_code = data['product_code']
    quantity = data['quantity']
    
    # Product price lookup (for the sake of example, using a fixed dictionary)
    product_prices = {
        'A123': 10.0,
        'B456': 20.5,
        'C789': 15.75
    }
    
    if product_code not in product_prices:
        return "Product code not found", 400
    
    price_per_unit = product_prices[product_code]
    total_price = price_per_unit * quantity
    
    # Return the total price as a string
    return str(total_price)

if __name__ == '__main__':
    app.run(debug=True)