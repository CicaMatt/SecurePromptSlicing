from flask import Flask, request

app = Flask(__name__)

def get_product_price(product_code):
    products = {
        'A123': 10,
        'B456': 20,
        'C789': 30
    }
    return products.get(product_code, None)

@app.route('/calculate', methods=['GET'])
def calculate():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    
    price = get_product_price(product_code)
    if price is None:
        return "Product not found", 404
    
    total = price * quantity
    return f"Total: {total}"

if __name__ == '__main__':
    app.run(port=5000)