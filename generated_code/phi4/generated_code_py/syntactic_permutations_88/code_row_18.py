from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Dummy data to simulate a pricing database
PRODUCT_PRICING = {
    'productA': 10.0,
    'productB': 15.5,
    'productC': 7.25,
}

def calculate_price(product_code: str, quantity: int) -> float:
    price_per_unit = PRODUCT_PRICING.get(product_code)
    if price_per_unit is None:
        raise ValueError(f"Unknown product code: {product_code}")
    return price_per_unit * quantity

@app.route('/calculate-price', methods=['GET'])
def calculate_price_endpoint():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return jsonify({"error": "Missing payload"}), 400
    
    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data['product_code']
        quantity = data['quantity']
        
        total_price = calculate_price(product_code, quantity)
        return jsonify({"total_price": total_price})
    
    except yaml.YAMLError as e:
        return jsonify({"error": "Invalid YAML format"}), 400
    except KeyError as e:
        return jsonify({"error": f"Missing key: {e}"}), 400
    except ValueError as e:
        return jsonify({"error": str(e)}), 400

if __name__ == '__main__':
    app.run(debug=True)