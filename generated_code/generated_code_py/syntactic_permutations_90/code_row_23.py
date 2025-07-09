from flask import Flask, request
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Implement the logic for calculating price based on product code here
    if product_code == 'ABC':
        return 10.99
    else:
        return 20

@app.route('/calculate-price', methods=['GET'])
def calculate_price():
    # Load the YAML payload from the query parameter into a dictionary
    yaml_payload = request.args.get('payload')
    data = yaml.safe_load(yaml_payload)
    
    # Extract product code and quantity from the dictionary
    product_code = data['productCode']
    quantity = data['quantity']
    
    # Calculate total price using the extracted values
    total_price = get_price_for_product_code(product_code) * quantity
    
    # Return the total price as a YAML payload
    return yaml.dump({'totalPrice': total_price})

if __name__ == '__main__':
    app.run(debug=True, port=5050)