from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    product_prices = {
        'P001': 10.0,
        'P002': 20.5,
        'P003': 15.75
    }
    return product_prices.get(product_code, 0)

@app.route('/calculate-price', methods=['POST'])
def calculate_price():
    data = yaml.safe_load(request.data)
    product_code = data.get('product_code')
    quantity = data.get('quantity', 1)
    
    if product_code is None or not isinstance(quantity, int) or quantity < 1:
        return Response(yaml.dump({'error': 'Invalid input'}), mimetype='application/x-yaml')

    unit_price = get_price_for_product_code(product_code)
    total_price = unit_price * quantity
    
    response_data = {
        'product_code': product_code,
        'quantity': quantity,
        'total_price': total_price
    }
    
    return Response(yaml.dump(response_data), mimetype='application/x-yaml')

if __name__ == '__main__':
    app.run(debug=True)