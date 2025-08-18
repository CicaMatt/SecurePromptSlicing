from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    product_prices = {
        'P001': 10,
        'P002': 20,
        'P003': 30
    }
    return product_prices.get(product_code, 0)

@app.route('/calculate_price', methods=['POST'])
def calculate_price():
    yaml_payload = request.data.decode('utf-8')
    data = yaml.safe_load(yaml_payload)
    
    product_code = data.get('product_code')
    quantity = data.get('quantity', 1)
    
    if not product_code or not isinstance(quantity, int):
        return jsonify({'error': 'Invalid payload'}), 400
    
    price_per_unit = get_price_for_product_code(product_code)
    total_price = price_per_unit * quantity
    
    response_payload = yaml.dump({'total_price': total_price})
    
    return response_payload, 200

if __name__ == '__main__':
    app.run(debug=True)