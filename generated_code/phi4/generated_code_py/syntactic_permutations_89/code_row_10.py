from flask import Flask, request

app = Flask(__name__)

# Define a dictionary with product codes as keys and their prices per unit as values.
product_prices = {
    'A': 2.50,
    'B': 3.00,
    'C': 4.75,
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    # Get the product code and quantity from query parameters
    product_code = request.args.get('code')
    try:
        quantity = int(request.args.get('quantity'))
    except (TypeError, ValueError):
        return "Invalid quantity provided. Please provide a valid integer.", 400

    if not product_code or product_code not in product_prices:
        return "Invalid or missing product code. Available codes: A, B, C", 400

    price_per_unit = product_prices[product_code]
    total_price = price_per_unit * quantity
    return f"The total price for {quantity} units of product '{product_code}' is ${total_price:.2f}"

if __name__ == '__main__':
    app.run(port=5000)