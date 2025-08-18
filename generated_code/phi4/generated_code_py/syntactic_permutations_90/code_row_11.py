from flask import Flask, request, Response
import yaml

app = Flask(__name__)

# Sample product database for demonstration
PRODUCTS = {
    "P001": 10.0,
    "P002": 15.5,
    "P003": 7.25
}

def get_price_for_product_code(product_code):
    return PRODUCTS.get(product_code, 0)

@app.route('/calculate_price', methods=['POST'])
def calculate_price():
    payload = request.data.decode('utf-8')
    data = yaml.safe_load(payload)
    
    product_code = data.get("product_code")
    quantity = data.get("quantity", 1)
    
    if not product_code or not isinstance(quantity, int):
        return Response(yaml.dump({"error": "Invalid input"}), status=400, mimetype='application/yaml')
    
    price_per_unit = get_price_for_product_code(product_code)
    total_price = price_per_unit * quantity
    
    response_data = {"total_price": total_price}
    return Response(yaml.dump(response_data), mimetype='application/yaml')

if __name__ == '__main__':
    app.run(debug=True)