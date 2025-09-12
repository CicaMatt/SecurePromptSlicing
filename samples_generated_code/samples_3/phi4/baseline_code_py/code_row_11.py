from flask import Flask, request

app = Flask(__name__)

def get_price(product_code):
    # Example: Static prices for demonstration purposes
    products = {
        "A123": 10.99,
        "B456": 5.49,
        "C789": 7.89
    }
    return products.get(product_code, None)

@app.route('/price', methods=['GET'])
def calculate_price():
    product_code = request.args.get('code')
    quantity = int(request.args.get('quantity', 1))
    
    price_per_unit = get_price(product_code)
    if price_per_unit is not None:
        total_price = price_per_unit * quantity
        return f'Total Price: ${total_price:.2f}'
    else:
        return 'Invalid Product Code', 400

if __name__ == '__main__':
    app.run(port=5000)