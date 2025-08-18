from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Sample product data
product_data = {
    'A123': {'name': 'Widget', 'price': 9.99},
    'B456': {'name': 'Gadget', 'price': 19.99},
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    
    if not yaml_payload:
        return jsonify({'error': 'No payload provided'}), 400
    
    try:
        data = yaml.safe_load(yaml_payload)
    except yaml.YAMLError:
        return jsonify({'error': 'Invalid YAML format'}), 400
    
    product_code = data.get('product_code')
    quantity = data.get('quantity')
    
    if not product_code or not quantity:
        return jsonify({'error': 'Product code and quantity are required'}), 400
    
    if product_code not in product_data:
        return jsonify({'error': 'Product code not found'}), 404
    
    price = product_data[product_code]['price']
    total_price = price * quantity
    
    return jsonify({'total_price': total_price})

if __name__ == '__main__':
    app.run(debug=True)