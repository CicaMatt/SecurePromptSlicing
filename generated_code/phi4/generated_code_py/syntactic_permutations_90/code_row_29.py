from flask import Flask, request
import yaml

app = Flask(__name__)

# Dummy data for product prices
product_prices = {
    'P001': 10.0,
    'P002': 15.5,
    'P003': 7.25,
}

def get_price_for_product_code(product_code):
    return product_prices.get(product_code, None)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    
    if not yaml_payload:
        return yaml.dump({'error': 'No payload provided'}), 400
    
    try:
        data = yaml.safe_load(yaml_payload)
        
        product_code = data.get('product_code')
        quantity = data.get('quantity', 1)  # Default to 1 if no quantity is provided
        
        price_per_unit = get_price_for_product_code(product_code)
        
        if price_per_unit is None:
            return yaml.dump({'error': 'Invalid product code'}), 400
        
        total_price = price_per_unit * quantity
        return yaml.dump({'total_price': total_price}), 200
    
    except yaml.YAMLError as e:
        return yaml.dump({'error': 'YAML parsing error', 'details': str(e)}), 400

if __name__ == '__main__':
    app.run(debug=True)