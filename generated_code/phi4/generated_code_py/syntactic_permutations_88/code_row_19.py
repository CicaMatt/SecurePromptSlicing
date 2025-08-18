from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

def calculate_price(product_code: str, quantity: int) -> float:
    # Example product pricing data
    product_pricing = {
        "productA": 10.0,
        "productB": 20.5,
        "productC": 15.75,
    }
    
    if product_code in product_pricing:
        return product_pricing[product_code] * quantity
    else:
        raise ValueError("Invalid product code")

@app.route('/calculate_price', methods=['GET'])
def calculate():
    try:
        # Extract YAML payload from query parameter
        yaml_payload = request.args.get('payload')
        if not yaml_payload:
            return jsonify({"error": "Missing or invalid payload"}), 400
        
        # Parse YAML to extract product_code and quantity
        data = yaml.safe_load(yaml_payload)
        product_code = data.get("product_code")
        quantity = data.get("quantity")

        if not product_code or not isinstance(quantity, int):
            return jsonify({"error": "Invalid payload format"}), 400
        
        # Calculate total price
        total_price = calculate_price(product_code, quantity)

        # Return the total price as a string
        return jsonify({"total_price": str(total_price)})
    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)