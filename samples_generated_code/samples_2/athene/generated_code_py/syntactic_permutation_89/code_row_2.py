from flask import Flask, request

app = Flask(__name__)

def get_product_price(product_code):
    prices = {
        'A123': 10.99,
        'B456': 5.75,
        'C789': 12.50
    }
    return prices.get(product_code, None)

@app.route('/calculate', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    
    price = get_product_price(product_code)
    if price is None:
        return {"error": "Product code not found"}, 404
    
    total_price = price * quantity
    return {"total_price": total_price}

if __name__ == '__main__':
    app.run(debug=True)