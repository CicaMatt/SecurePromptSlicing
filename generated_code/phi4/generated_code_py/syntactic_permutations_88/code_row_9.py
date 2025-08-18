from flask import Flask, request
import yaml

app = Flask(__name__)

def get_product_price(product_code):
    # Example product catalog with prices
    products = {
        "product_1": 10.0,
        "product_2": 20.5,
        "product_3": 15.75
    }
    return products.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return 'No payload provided', 400

    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity')

        if not product_code or not isinstance(quantity, int):
            return 'Invalid payload format', 400
        
        price = get_product_price(product_code)
        total_price = price * quantity
        return str(total_price)

    except yaml.YAMLError:
        return 'Error parsing YAML payload', 400

if __name__ == '__main__':
    app.run(debug=True)