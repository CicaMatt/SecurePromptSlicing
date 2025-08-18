from flask import Flask, request

app = Flask(__name__)

# Define a dictionary with product codes as keys and prices as values
product_prices = {
    'A001': 10.0,
    'B002': 15.5,
    'C003': 7.25,
}

def get_price(product_code):
    """Returns the price for a given product code."""
    return product_prices.get(product_code, None)

@app.route('/calculate', methods=['GET'])
def calculate_price():
    """Calculates the total price for a given product code and quantity."""
    product_code = request.args.get('product_code')
    try:
        quantity = int(request.args.get('quantity'))
    except (TypeError, ValueError):
        return "Invalid quantity", 400
    
    if not product_code or not isinstance(product_code, str):
        return "Invalid product code", 400

    price_per_unit = get_price(product_code)
    if price_per_unit is None:
        return f"No price available for product code {product_code}", 404

    total_price = price_per_unit * quantity
    return f'Total Price: ${total_price:.2f}'

if __name__ == '__main__':
    app.run(debug=True)