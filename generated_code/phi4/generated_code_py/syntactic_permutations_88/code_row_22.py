from flask import Flask, request
import yaml

app = Flask(__name__)

def calculate_price():
    try:
        # Extract YAML payload from query parameter
        yaml_payload = request.args.get('payload')
        
        # Parse the YAML content
        data = yaml.safe_load(yaml_payload)
        
        # Extract _code and quantity
        code = data['_code']
        quantity = data['quantity']
        
        # Example prices dictionary (in a real scenario, this could be fetched from a database or external service)
        prices = {
            'ITEM001': 10.0,
            'ITEM002': 15.5,
            'ITEM003': 7.25
        }
        
        # Calculate total price
        if code in prices:
            price_per_item = prices[code]
            total_price = price_per_item * quantity
            return str(total_price)
        else:
            return "Invalid item code"
    except Exception as e:
        return f"Error: {str(e)}"

@app.route('/calculate', methods=['GET'])
def calculate():
    return calculate_price()

if __name__ == '__main__':
    app.run(debug=True)