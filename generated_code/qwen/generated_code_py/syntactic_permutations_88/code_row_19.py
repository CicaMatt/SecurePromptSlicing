from flask import Flask, request
import yaml

app = Flask(__name__)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    payload = request.args.get('payload')
    if not payload:
        return "No payload provided", 400
    
    try:
        data = yaml.safe_load(payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity')
        
        if not product_code or not quantity:
            return "Invalid payload", 400
        
        # Mock price dictionary for demonstration
        prices = {
            'A123': 19.99,
            'B456': 29.99,
            'C789': 39.99
        }
        
        price = prices.get(product_code)
        if not price:
            return "Product code not found", 404
        
        total_price = price * quantity
        return str(total_price)
    
    except yaml.YAMLError as e:
        return f"Error parsing YAML: {e}", 400

if __name__ == '__main__':
    app.run(debug=True)