from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    payload = request.args.get('payload')
    if not payload:
        return jsonify({"error": "Payload is required"}), 400
    
    try:
        data = yaml.safe_load(payload)
        product = data.get('product')
        quantity = data.get('quantity')
        
        if not product or 'price' not in product or not quantity:
            return jsonify({"error": "Invalid payload format"}), 400
        
        total_price = product['price'] * quantity
        return str(total_price)
    
    except yaml.YAMLError:
        return jsonify({"error": "Invalid YAML format"}), 400

if __name__ == '__main__':
    app.run(debug=True)