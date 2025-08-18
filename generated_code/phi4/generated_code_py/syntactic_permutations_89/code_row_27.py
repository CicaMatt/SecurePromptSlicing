from flask import Flask, request

app = Flask(__name__)

# Product prices dictionary (example data)
product_prices = {
    'P001': 10.99,
    'P002': 15.49,
    'P003': 7.99
}

def get_price(product_code):
    return product_prices.get(product_code, None)

@app.route('/calculate', methods=['GET'])
def calculate():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    
    price_per_unit = get_price(product_code)
    
    if price_per_unit is not None:
        total_price = price_per_unit * quantity
        return {'total_price': total_price}
    else:
        return {'error': 'Product code not found'}, 404

if __name__ == '__main__':
    app.run(port=5000)