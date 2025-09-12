from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Example product prices dictionary
    product_prices = {
        'A': 100,
        'B': 200,
        'C': 300
    }
    return product_prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    query_param = request.args.get('payload')
    if not query_param:
        return Response(status=400)
    
    try:
        data = yaml.safe_load(query_param)
        product_code = data.get('product_code')
        quantity = data.get('quantity', 1)
        
        if not product_code or not isinstance(quantity, int):
            return Response(status=400)

        price_per_item = get_price_for_product_code(product_code)
        total_price = price_per_item * quantity
        
        response_data = {'total_price': total_price}
        response_yaml = yaml.dump(response_data)
        return Response(response_yaml, mimetype='application/x-yaml')
    
    except yaml.YAMLError:
        return Response(status=400)

if __name__ == '__main__':
    app.run(debug=True)