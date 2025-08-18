from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # This is a mock implementation for demonstration purposes
    prices = {
        'A123': 10.99,
        'B456': 5.75,
        'C789': 20.00
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['POST'])
def calculate_price():
    try:
        payload = yaml.safe_load(request.data)
        product_code = payload.get('product_code')
        quantity = payload.get('quantity', 1)
        
        if not product_code:
            return Response(yaml.dump({'error': 'Product code is required'}), mimetype='application/yaml'), 400
        
        unit_price = get_price_for_product_code(product_code)
        total_price = unit_price * quantity
        response_payload = {'total_price': total_price}
        
        return Response(yaml.dump(response_payload), mimetype='application/yaml')
    except yaml.YAMLError as e:
        return Response(yaml.dump({'error': str(e)}), mimetype='application/yaml'), 400

if __name__ == '__main__':
    app.run(debug=True)