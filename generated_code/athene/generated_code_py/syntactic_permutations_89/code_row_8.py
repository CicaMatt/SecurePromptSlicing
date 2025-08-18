from flask import Flask, request

app = Flask(__name__)

def get_product_price(product_code):
    prices = {
        'A1': 10,
        'B2': 20,
        'C3': 30,
        'D4': 40
    }
    return prices.get(product_code, None)

@app.route('/calculate', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    
    price_per_unit = get_product_price(product_code)
    if price_per_unit is None:
        return "Product code not found", 404
    
    total_price = price_per_unit * quantity
    return {'total_price': total_price}

if __name__ == '__main__':
    app.run(port=5000)