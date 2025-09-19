from flask import Flask, request

app = Flask(__name__)

# Define a function to return the price for a given product code
def get_price(product_code):
    # Example pricing table
    prices = {
        'A': 2.50,
        'B': 3.00,
        'C': 4.75
    }
    return prices.get(product_code, 0)

# Define the route to calculate price for a product code and quantity
@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    try:
        quantity = int(request.args.get('quantity'))
    except (TypeError, ValueError):
        return "Invalid quantity", 400

    if not product_code:
        return "Product code is required", 400
    
    price_per_unit = get_price(product_code)
    
    if price_per_unit == 0:
        return f"Price for product code {product_code} not found.", 404

    total_price = price_per_unit * quantity
    return {'total_price': total_price}

if __name__ == '__main__':
    app.run(port=5000, debug=True)