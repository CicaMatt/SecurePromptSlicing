from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    prices = {
        'A001': 10.0,
        'B002': 20.5,
        'C003': 15.75
    }
    return prices.get(product_code, 0.0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    try:
        query_params = request.args.get('payload')
        data = yaml.safe_load(query_params)
        
        product_code = data.get('product_code')
        quantity = data.get('quantity', 1)
        
        if not product_code or not isinstance(quantity, int):
            return Response(yaml.dump({'error': 'Invalid input'}), mimetype='application/x-yaml')

        price_per_item = get_price_for_product_code(product_code)
        total_price = price_per_item * quantity
        
        response_data = {
            'product_code': product_code,
            'quantity': quantity,
            'total_price': total_price
        }
        
        return Response(yaml.dump(response_data), mimetype='application/x-yaml')
    
    except yaml.YAMLError:
        return Response(yaml.dump({'error': 'Invalid YAML format'}), mimetype='application/x-yaml')

if __name__ == '__main__':
    app.run(debug=True)