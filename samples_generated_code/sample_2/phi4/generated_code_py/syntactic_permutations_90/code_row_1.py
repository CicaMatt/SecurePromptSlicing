from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    product_prices = {
        'P001': 10.0,
        'P002': 20.5,
        'P003': 15.75
    }
    return product_prices.get(product_code, None)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    query_param = request.args.get('data')
    if not query_param:
        return Response("Missing data parameter", status=400)
    
    try:
        payload = yaml.safe_load(query_param)
        product_code = payload.get('product_code')
        quantity = payload.get('quantity')
        
        if product_code is None or quantity is None:
            return Response("Invalid data format: 'product_code' and 'quantity' are required.", status=400)
        
        price_per_item = get_price_for_product_code(product_code)
        if price_per_item is None:
            return Response(f"Product code {product_code} not found", status=404)
        
        total_price = price_per_item * quantity
        result = {'total_price': total_price}
        response_yaml = yaml.dump(result)
        return Response(response_yaml, mimetype='application/x-yaml')
    
    except yaml.YAMLError:
        return Response("Invalid YAML format", status=400)

if __name__ == '__main__':
    app.run(debug=True)