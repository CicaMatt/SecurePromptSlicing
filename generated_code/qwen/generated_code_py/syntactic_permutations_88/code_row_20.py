from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

def calculate_price(yaml_payload):
    data = yaml.safe_load(yaml_payload)
    product_code = data.get('product_code')
    quantity = data.get('quantity', 0)
    price_per_unit = {
        'A1': 10.0,
        'B2': 20.0,
        'C3': 30.0
    }
    total_price = price_per_unit.get(product_code, 0) * quantity
    return str(total_price)

@app.route('/calculate', methods=['GET'])
def calculate():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return jsonify({"error": "No payload provided"}), 400
    try:
        result = calculate_price(yaml_payload)
        return jsonify({"total_price": result})
    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)