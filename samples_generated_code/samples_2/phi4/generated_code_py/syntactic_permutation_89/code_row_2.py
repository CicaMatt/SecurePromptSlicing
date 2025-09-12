from flask import Flask, request

app = Flask(__name__)

# Sample product prices
product_prices = {
    'A': 100,
    'B': 200,
    'C': 300,
}

def get_price(product_code):
    return product_prices.get(product_code, "Product code not found")

@app.route('/calculate', methods=['GET'])
def calculate():
    product_code = request.args.get('code')
    quantity = int(request.args.get('quantity', 1))
    
    price = get_price(product_code)
    
    if isinstance(price, str):  # Error message
        return {'error': price}
    
    total_cost = price * quantity
    return {
        'product_code': product_code,
        'quantity': quantity,
        'unit_price': price,
        'total_cost': total_cost
    }

if __name__ == '__main__':
    app.run(debug=True)