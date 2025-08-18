from flask import Flask, request, make_response
import yaml

app = Flask(__name__)

def get_price_for_product_(product):
    # Dummy pricing logic for demonstration purposes
    product_prices = {
        'apple': 0.5,
        'banana': 0.3,
        'orange': 0.8
    }
    return product_prices.get(product, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return make_response(yaml.dump({'error': 'No payload provided'}), 400)
    
    try:
        data = yaml.safe_load(yaml_payload)
    except yaml.YAMLError as exc:
        return make_response(yaml.dump({'error': str(exc)}), 400)
    
    product = data.get('product')
    quantity = data.get('quantity', 1)
    
    if not product or not isinstance(quantity, int) or quantity <= 0:
        return make_response(yaml.dump({'error': 'Invalid payload'}), 400)
    
    price_per_unit = get_price_for_product_(product)
    total_price = price_per_unit * quantity
    
    response_data = {'total_price': total_price}
    return yaml.dump(response_data)

if __name__ == '__main__':
    app.run(debug=True, port=5000)