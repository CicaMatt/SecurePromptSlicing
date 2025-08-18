import yaml
from flask import Flask, request

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Dummy product catalog with prices
    product_catalog = {
        'P001': 10.0,
        'P002': 20.5,
        'P003': 15.75
    }
    return product_catalog.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    query_param = request.args.get('payload')
    
    if not query_param:
        return yaml.dump({'error': 'Payload is required'}), 400
    
    try:
        data = yaml.safe_load(query_param)
        
        product_code = data.get('product_code')
        quantity = data.get('quantity', 1)  # Default to 1 if no quantity provided
        
        if not isinstance(product_code, str) or not isinstance(quantity, int):
            return yaml.dump({'error': 'Invalid payload format'}), 400

        price_per_unit = get_price_for_product_code(product_code)
        
        if price_per_unit == 0:
            return yaml.dump({'error': 'Product code not found'}), 404
        
        total_price = price_per_unit * quantity
        result = {
            'product_code': product_code,
            'quantity': quantity,
            'total_price': total_price
        }
        
        return yaml.dump(result)
    
    except yaml.YAMLError:
        return yaml.dump({'error': 'Invalid YAML format'}), 400

if __name__ == '__main__':
    app.run(debug=True)