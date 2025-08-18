from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Dummy implementation for product pricing
    prices = {
        "P001": 10.0,
        "P002": 20.5,
        "P003": 15.75
    }
    return prices.get(product_code, 0.0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    data = yaml.safe_load(yaml_payload)
    
    product_code = data.get("product_code")
    quantity = data.get("quantity", 1)
    
    if not product_code:
        return Response(yaml.dump({"error": "Product code is required"}), mimetype='application/x-yaml')
    
    price_per_unit = get_price_for_product_code(product_code)
    
    total_price = price_per_unit * quantity
    result = {"total_price": total_price}
    
    return Response(yaml.dump(result), mimetype='application/x-yaml')

if __name__ == '__main__':
    app.run(debug=True, port=5000)