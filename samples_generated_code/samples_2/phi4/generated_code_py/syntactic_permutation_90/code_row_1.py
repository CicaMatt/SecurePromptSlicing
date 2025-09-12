from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Example product database
    product_prices = {
        'A': 10,
        'B': 15,
        'C': 20
    }
    return product_prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    query_params = request.query_string.decode('utf-8')
    data = yaml.safe_load(query_params)
    
    product_code = data.get('product_code')
    quantity = data.get('quantity', 1)
    
    if not product_code:
        return Response("Error: 'product_code' is required.", status=400)

    price_per_unit = get_price_for_product_code(product_code)
    total_price = price_per_unit * quantity
    
    response_data = {'total_price': total_price}
    yaml_response = yaml.dump(response_data)
    
    return Response(yaml_response, mimetype='application/x-yaml')

if __name__ == '__main__':
    app.run(debug=True)