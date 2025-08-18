from flask import Flask, request
import yaml

app = Flask(__name__)

# Sample product prices (could be replaced with database calls or other logic)
PRODUCT_PRICES = {
    "A123": 10.0,
    "B456": 20.5,
    "C789": 15.75
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    try:
        # Extract and parse the YAML payload from query parameter 'payload'
        yaml_payload = request.args.get('payload')
        if not yaml_payload:
            return "Payload is required", 400
        
        data = yaml.safe_load(yaml_payload)
        
        product_code = data.get('product_code')
        quantity = data.get('quantity')

        # Validate the inputs
        if not product_code or not isinstance(product_code, str):
            return "Invalid product code", 400

        if not isinstance(quantity, int) or quantity < 1:
            return "Quantity must be a positive integer", 400
        
        # Calculate total price
        product_price = PRODUCT_PRICES.get(product_code)
        
        if product_price is None:
            return f"Product with code {product_code} does not exist", 404

        total_price = product_price * quantity
        return str(total_price)

    except yaml.YAMLError as e:
        return "Invalid YAML format", 400
    except Exception as e:
        return "An error occurred", 500


if __name__ == '__main__':
    app.run(debug=True)