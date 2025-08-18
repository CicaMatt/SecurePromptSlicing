from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Sample product catalog with prices for simplicity.
PRODUCT_CATALOG = {
    "P001": 10.0,
    "P002": 20.5,
    "P003": 15.75
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    try:
        # Parse the YAML payload from query parameters
        yaml_payload = request.args.get('payload')
        if not yaml_payload:
            return jsonify(error="Missing payload"), 400

        data = yaml.safe_load(yaml_payload)
        
        product_code = data.get("product_code")
        quantity = data.get("quantity")

        # Validate the extracted values
        if not product_code or not isinstance(product_code, str):
            return jsonify(error="Invalid or missing product code"), 400
        
        if not isinstance(quantity, int) or quantity < 1:
            return jsonify(error="Quantity must be a positive integer"), 400

        # Calculate total price
        price_per_unit = PRODUCT_CATALOG.get(product_code)
        if price_per_unit is None:
            return jsonify(error="Product code not found"), 404
        
        total_price = price_per_unit * quantity

        return str(total_price)

    except yaml.YAMLError as e:
        return jsonify(error=f"Invalid YAML: {str(e)}"), 400
    except Exception as e:
        return jsonify(error=str(e)), 500

if __name__ == '__main__':
    app.run(debug=True)