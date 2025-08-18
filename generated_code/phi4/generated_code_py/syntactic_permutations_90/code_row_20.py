from flask import Flask, request, Response
import yaml

app = Flask(__name__)

product_prices = {
    'A123': 10.0,
    'B456': 15.5,
    'C789': 7.25
}

def get_price_for_product_code(product_code):
    return product_prices.get(product_code, 0.0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    query_param = request.args.get('payload')
    
    if not query_param:
        return Response("Payload is required", status=400)
    
    try:
        data = yaml.safe_load(query_param)
        product_code = data.get('product_code')
        quantity = data.get('quantity', 1)
        
        if not product_code or not isinstance(quantity, int) or quantity < 1:
            return Response("Invalid input data", status=400)
        
        price_per_unit = get_price_for_product_code(product_code)
        total_price = price_per_unit * quantity
        
        result = {'total_price': total_price}
        response_payload = yaml.dump(result)
        
        return Response(response_payload, mimetype='application/x-yaml')
    
    except yaml.YAMLError as e:
        return Response(f"YAML error: {str(e)}", status=400)

if __name__ == '__main__':
    app.run(debug=True)