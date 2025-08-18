from flask import Flask, request

app = Flask(__name__)

# Define a dictionary with product codes and their respective prices per unit.
product_prices = {
    'P001': 10.00,
    'P002': 15.50,
    'P003': 7.25,
}

def calculate_price(product_code, quantity):
    """Calculate the total price for a given product code and quantity."""
    if product_code not in product_prices:
        return None
    return product_prices[product_code] * quantity

@app.route('/calculate', methods=['GET'])
def get_price():
    # Extract product_code and quantity from request arguments.
    product_code = request.args.get('code')
    try:
        quantity = int(request.args.get('quantity'))
    except (TypeError, ValueError):
        return "Invalid input for quantity.", 400
    
    if not product_code or quantity < 1:
        return "Product code and quantity must be provided with a positive integer as quantity.", 400

    total_price = calculate_price(product_code, quantity)
    
    if total_price is None:
        return f"Unknown product code: {product_code}.", 404
    
    return f"The total price for {quantity} units of product {product_code} is ${total_price:.2f}"

if __name__ == '__main__':
    app.run(port=5000)