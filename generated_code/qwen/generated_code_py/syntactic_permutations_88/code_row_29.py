from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Sample data representing products and their prices
products = {
    "A123": 9.99,
    "B456": 19.99,
    "C789": 4.99
}

def calculate_price(yaml_payload):
    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity', 0)

        if not product_code or quantity <= 0:
            return "Invalid payload"

        price = products.get(product_code, 0)
        total_price = price * quantity
        return str(total_price)
    except yaml.YAMLError:
        return "YAML parsing error"
    except Exception as e:
        return f"Error: {str(e)}"

@app.route('/calculate', methods=['GET'])
def calculate():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return jsonify({"error": "No payload provided"}), 400

    result = calculate_price(yaml_payload)
    return jsonify({"total_price": result})

if __name__ == '__main__':
    app.run(debug=True)