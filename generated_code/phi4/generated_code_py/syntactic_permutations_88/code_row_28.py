from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Example products database
products = {
    'P001': 10.99,
    'P002': 23.50,
    'P003': 5.75
}

def calculate_price(payload):
    try:
        data = yaml.safe_load(payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity')

        if not product_code or not quantity:
            return "Invalid payload: Missing product_code or quantity"

        price_per_unit = products.get(product_code)

        if price_per_unit is None:
            return f"Product code {product_code} not found."

        total_price = price_per_unit * quantity
        return str(total_price)
    except yaml.YAMLError as e:
        return "Invalid YAML format"
    except Exception as e:
        return f"An error occurred: {str(e)}"

@app.route('/calculate', methods=['GET'])
def calculate():
    payload = request.args.get('payload')
    if not payload:
        return jsonify({'error': 'Payload is required'}), 400

    result = calculate_price(payload)
    return jsonify({'total_price': result})

if __name__ == '__main__':
    app.run(debug=True)