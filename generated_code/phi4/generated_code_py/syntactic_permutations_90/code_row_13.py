from flask import Flask, request
import yaml

app = Flask(__name__)

# Sample product catalog with prices
PRODUCT_CATALOG = {
    "P001": 10.99,
    "P002": 15.49,
    "P003": 7.99,
}

def get_price_for_product_code(product_code):
    return PRODUCT_CATALOG.get(product_code, None)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    query_params = request.args.to_dict()
    
    product_data_yaml = query_params.get('product_data')
    if not product_data_yaml:
        return "Invalid input", 400
    
    try:
        product_data = yaml.safe_load(product_data_yaml)
    except yaml.YAMLError as e:
        return f"Failed to parse YAML: {str(e)}", 400

    product_code = product_data.get('product_code')
    quantity = product_data.get('quantity', 1) # Default to 1 if not provided

    price_per_unit = get_price_for_product_code(product_code)
    if price_per_unit is None:
        return "Product code not found", 404
    
    total_price = price_per_unit * quantity
    return f"Total price: {total_price:.2f}", 200

if __name__ == '__main__':
    app.run(debug=True, port=5000)


This code sets up a simple Flask web service with two functions. `get_price_for_product_code()` retrieves the price for a given product code from a predefined catalog. The `/calculate_price` route processes a request containing YAML-formatted data about a product and its quantity, calculating the total cost accordingly.