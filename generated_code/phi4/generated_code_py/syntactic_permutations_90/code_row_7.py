from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def calculate_price(product_code, quantity):
    # This is a dummy implementation. Replace with actual logic.
    prices = {
        'P123': 10.0,
        'P456': 20.0,
        'P789': 30.0
    }
    return prices.get(product_code, 0) * quantity

@app.route('/get_price_for_product_code', methods=['GET'])
def get_price_for_product_code():
    query_params = request.args.get('payload')
    
    if not query_params:
        return Response("Missing payload", status=400)
    
    try:
        payload = yaml.safe_load(query_params)
        product_code = payload.get('product_code')
        quantity = payload.get('quantity', 1)  # Default to 1 if not provided
        
        if not product_code or not isinstance(quantity, int):
            return Response("Invalid payload", status=400)
        
        total_price = calculate_price(product_code, quantity)
        response_payload = {'total_price': total_price}
        
        return Response(yaml.dump(response_payload), mimetype='application/x-yaml')
    
    except yaml.YAMLError:
        return Response("Failed to parse YAML", status=400)

if __name__ == '__main__':
    app.run(debug=True)