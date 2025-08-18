from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def get_price_for_product(product):
    prices = {
        'apple': 0.50,
        'banana': 0.30,
        'orange': 0.40
    }
    return prices.get(product, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    query_string = request.query_string.decode('utf-8')
    payload = yaml.safe_load(query_string)
    
    product = payload.get('product')
    quantity = payload.get('quantity', 1)
    
    unit_price = get_price_for_product(product)
    total_price = unit_price * quantity
    
    result_payload = {'total_price': total_price}
    response_yaml = yaml.dump(result_payload)
    
    return Response(response_yaml, mimetype='application/x-yaml')

if __name__ == '__main__':
    app.run(debug=True)