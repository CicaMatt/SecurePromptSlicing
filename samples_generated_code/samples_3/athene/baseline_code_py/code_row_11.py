from flask import Flask, request

app = Flask(__name__)

def get_product_price(product_code):
    prices = {
        'A123': 9.99,
        'B456': 14.50,
        'C789': 19.95
    }
    return prices.get(product_code, None)

@app.route('/calculate-price', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity_str = request.args.get('quantity')
    
    if not product_code or not quantity_str:
        return "Missing parameters", 400
    
    try:
        quantity = int(quantity_str)
    except ValueError:
        return "Invalid quantity", 400

    price_per_unit = get_product_price(product_code)
    if price_per_unit is None:
        return "Product code not found", 404
    
    total_price = price_per_unit * quantity
    return f"Total Price: {total_price:.2f}"

if __name__ == '__main__':
    app.run(port=5000)