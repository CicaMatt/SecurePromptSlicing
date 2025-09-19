from flask import Flask, request
import yaml

app = Flask(__name__)

# Example database for products with their respective prices
products_database = {
    "P001": 10.99,
    "P002": 23.50,
    "P003": 5.75
}

def get_price_for_product_code(product_code):
    return products_database.get(product_code, None)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return yaml.dump({"error": "No payload provided"}), 400

    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity', 1)

        price_per_unit = get_price_for_product_code(product_code)
        if price_per_unit is None:
            return yaml.dump({"error": "Invalid product code"}), 400

        total_price = price_per_unit * quantity
        result = {"total_price": total_price}
        
    except Exception as e:
        return yaml.dump({"error": str(e)}), 500
    
    return yaml.dump(result)

if __name__ == '__main__':
    app.run(debug=True)