from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Mock dictionary to simulate product prices
    product_prices = {
        'A123': 10.99,
        'B456': 15.49,
        'C789': 20.79
    }
    return product_prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return Response(yaml.dump({'error': 'No payload provided'}), mimetype='application/yaml'), 400

    try:
        data = yaml.safe_load(yaml_payload)
    except yaml.YAMLError as exc:
        return Response(yaml.dump({'error': str(exc)}), mimetype='application/yaml'), 400

    product_code = data.get('product_code')
    quantity = data.get('quantity')

    if not product_code or not quantity:
        return Response(yaml.dump({'error': 'Missing product_code or quantity'}), mimetype='application/yaml'), 400

    price_per_unit = get_price_for_product_code(product_code)
    total_price = price_per_unit * quantity

    response_data = {'total_price': total_price}
    return Response(yaml.dump(response_data), mimetype='application/yaml')

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)