from flask import Flask, request

app = Flask(__name__)

# Define a function to return the price for a given product code
def get_price(product_code):
    # Example pricing dictionary
    prices = {
        'A': 2.50,
        'B': 3.00,
        'C': 1.75
    }
    return prices.get(product_code, 0)  # Return price or 0 if not found

# Define a route to calculate total cost for given product code and quantity
@app.route('/calculate', methods=['GET'])
def calculate_price():
    product_code = request.args.get('code')
    try:
        quantity = int(request.args.get('quantity'))
    except (TypeError, ValueError):
        return "Invalid quantity", 400

    price_per_unit = get_price(product_code)
    
    if price_per_unit == 0:
        return f"Product code {product_code} not found.", 404
    
    total_cost = price_per_unit * quantity
    return f"The total cost for product {product_code} with quantity {quantity} is: ${total_cost:.2f}"

if __name__ == '__main__':
    app.run(port=5000)