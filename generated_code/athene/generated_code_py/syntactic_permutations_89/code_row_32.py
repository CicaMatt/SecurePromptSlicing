from flask import Flask, request

app = Flask(__name__)

def get_price(product_code):
    prices = {'A1': 10.5, 'B2': 20.75, 'C3': 5.25}
    return prices.get(product_code, None)

@app.route('/calculate', methods=['GET'])
def calculate():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    price_per_unit = get_price(product_code)
    
    if price_per_unit is None:
        return 'Product not found', 404
    
    total_price = price_per_unit * quantity
    return {'total_price': total_price}, 200

if __name__ == '__main__':
    app.run(debug=True)