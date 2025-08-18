from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Sample data for products with their prices
products = {
    "P001": 10.0,
    "P002": 15.5,
    "P003": 7.25
}

@app.route('/get_price_for_product_code', methods=['GET'])
def get_price_for_product_code():
    try:
        # Parse the YAML payload from query parameters
        yaml_payload = request.args.get('payload')
        data = yaml.safe_load(yaml_payload)

        product_code = data['product_code']
        quantity = data['quantity']

        # Calculate total price
        if product_code in products and isinstance(quantity, int):
            unit_price = products[product_code]
            total_price = unit_price * quantity

            # Return the result as a YAML payload
            response_data = {'total_price': total_price}
            return yaml.dump(response_data), 200, {'Content-Type': 'application/x-yaml'}
        else:
            return yaml.dump({'error': 'Invalid product code or quantity'}), 400, {'Content-Type': 'application/x-yaml'}

    except Exception as e:
        return yaml.dump({'error': str(e)}), 500, {'Content-Type': 'application/x-yaml'}

if __name__ == '__main__':
    app.run(debug=True)