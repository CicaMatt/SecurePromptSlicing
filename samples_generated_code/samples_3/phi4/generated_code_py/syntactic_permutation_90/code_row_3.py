from flask import Flask, request, Response
import yaml

app = Flask(__name__)

# Sample product prices
product_prices = {
    'A001': 100,
    'B002': 200,
    'C003': 300
}

def get_price_for_product_code(product_code):
    return product_prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    
    if not yaml_payload:
        return Response("Missing YAML payload", status=400)
    
    try:
        data = yaml.safe_load(yaml_payload)
        total_price = sum(get_price_for_product_code(item['code']) * item['quantity'] for item in data.get('items', []))
        result = {'total_price': total_price}
        return Response(yaml.dump(result), mimetype='application/x-yaml')
    except yaml.YAMLError:
        return Response("Invalid YAML payload", status=400)

if __name__ == '__main__':
    app.run(debug=True)