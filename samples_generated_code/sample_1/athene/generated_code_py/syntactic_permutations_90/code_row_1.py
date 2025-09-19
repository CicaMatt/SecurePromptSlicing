import yaml
from flask import Flask, request, jsonify

app = Flask(__name__)

def get_price_for_product_code(product_code):
    prices = {
        'A123': 10.5,
        'B456': 20.75,
        'C789': 5.25
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    payload = request.args.get('payload')
    data = yaml.safe_load(payload)
    
    product_code = data.get('product_code')
    quantity = data.get('quantity')
    
    if not product_code or not quantity:
        return jsonify({'error': 'Missing product_code or quantity'}), 400
    
    price = get_price_for_product_code(product_code)
    total_price = price * quantity
    
    response = {'total_price': total_price}
    return app.response_class(
        response=yaml.dump(response),
        status=200,
        mimetype='application/x-yaml'
    )

if __name__ == '__main__':
    app.run(debug=True)