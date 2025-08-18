from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

# Sample product data
product_data = {
    "A123": {"name": "Product A", "price": 10.99},
    "B456": {"name": "Product B", "price": 20.99},
    "C789": {"name": "Product C", "price": 15.99}
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('yaml')
    
    if not yaml_payload:
        return jsonify({"error": "YAML payload is required"}), 400
    
    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity', 1)
        
        if not product_code or not isinstance(quantity, int):
            return jsonify({"error": "Invalid payload format"}), 400
        
        product = product_data.get(product_code)
        
        if not product:
            return jsonify({"error": "Product not found"}), 404
        
        total_price = product['price'] * quantity
        return str(total_price)
    
    except yaml.YAMLError:
        return jsonify({"error": "Invalid YAML format"}), 400

if __name__ == '__main__':
    app.run(debug=True)