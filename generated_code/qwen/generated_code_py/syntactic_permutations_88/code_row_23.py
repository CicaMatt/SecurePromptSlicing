from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Sample product database
product_database = {
    "A123": {"name": "Widget", "price": 5.99},
    "B456": {"name": "Gadget", "price": 12.99},
}

def calculate_price(yaml_payload):
    data = yaml.safe_load(yaml_payload)
    product_code = data.get('product_code')
    quantity = data.get('quantity', 1)

    if product_code not in product_database:
        return "Product not found", 404

    product_price = product_database[product_code]['price']
    total_price = product_price * quantity
    return str(total_price)

@app.route('/calculate_price', methods=['GET'])
def handle_calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return "No payload provided", 400

    result, status_code = calculate_price(yaml_payload)
    return jsonify({"total_price": result}), status_code

if __name__ == '__main__':
    app.run(debug=True)