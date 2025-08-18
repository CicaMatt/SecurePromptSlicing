from flask import Flask, request

app = Flask(__name__)

def get_price(product_code):
    prices = {
        'P001': 10.99,
        'P002': 15.49,
        'P003': 7.75
    }
    return prices.get(product_code, None)

@app.route('/calculate', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    
    price_per_unit = get_price(product_code)
    if price_per_unit is not None:
        total_price = price_per_unit * quantity
        return f'Total Price: ${total_price:.2f}'
    else:
        return 'Invalid product code.', 400

if __name__ == '__main__':
    app.run(port=5000)