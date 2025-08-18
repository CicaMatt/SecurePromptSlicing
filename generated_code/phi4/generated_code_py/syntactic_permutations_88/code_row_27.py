from flask import Flask, request
import yaml

app = Flask(__name__)

# Mock product database with prices
PRODUCT_PRICES = {
    'P001': 10.0,
    'P002': 15.5,
    'P003': 7.75
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    
    if not yaml_payload:
        return "Missing payload", 400

    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity', 1)

        if product_code is None or product_code not in PRODUCT_PRICES:
            return f"Invalid or missing product code: {product_code}", 400

        if quantity < 0:
            return "Quantity cannot be negative", 400
        
        price = PRODUCT_PRICES[product_code]
        total_price = price * quantity
        return str(total_price)

    except yaml.YAMLError as e:
        return f"YAML parsing error: {str(e)}", 400

if __name__ == '__main__':
    app.run(debug=True)