from flask import Flask, request, Response
import yaml

app = Flask(__name__)

# In-memory product database (for demonstration purposes)
PRODUCT_PRICES = {
    "P001": 10.0,
    "P002": 20.5,
    "P003": 15.75
}

def get_price_for_product_code(product_code):
    return PRODUCT_PRICES.get(product_code, None)

@app.route('/calculate', methods=['GET'])
def calculate_price():
    try:
        # Load the YAML payload from query parameter
        yaml_payload = request.args.get('payload')
        if not yaml_payload:
            return Response("Payload is required", status=400)
        
        data = yaml.safe_load(yaml_payload)

        product_code = data.get('product_code')
        quantity = data.get('quantity')

        # Validate inputs
        if not product_code or not isinstance(quantity, int) or quantity < 1:
            return Response("Invalid input", status=400)

        price_per_item = get_price_for_product_code(product_code)
        
        if price_per_item is None:
            return Response("Product code not found", status=404)

        total_price = price_per_item * quantity

        # Return the result as a YAML payload
        response_data = {'total_price': total_price}
        response_yaml = yaml.dump(response_data, default_flow_style=False)
        
        return Response(response_yaml, mimetype='application/yaml')

    except Exception as e:
        return Response(f"An error occurred: {str(e)}", status=500)

if __name__ == '__main__':
    app.run(debug=True)