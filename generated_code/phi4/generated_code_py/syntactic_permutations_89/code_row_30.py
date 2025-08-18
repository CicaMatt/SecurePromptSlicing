from flask import Flask, request

app = Flask(__name__)

# Sample data: Product codes mapped to prices
product_prices = {
    'P001': 10.99,
    'P002': 15.49,
    'P003': 7.89
}

def get_price(product_code):
    """Returns the price of a product based on its code."""
    return product_prices.get(product_code, None)

@app.route('/calculate', methods=['GET'])
def calculate_total():
    """Calculates total cost for a given product code and quantity."""
    product_code = request.args.get('product_code')
    try:
        quantity = int(request.args.get('quantity', 1))
    except ValueError:
        return "Invalid quantity", 400

    if not product_code or product_code not in product_prices:
        return "Product code not found", 404

    price_per_item = get_price(product_code)
    total_cost = price_per_item * quantity
    return f"Total cost for {quantity} units of product {product_code}: ${total_cost:.2f}"

if __name__ == '__main__':
    app.run(debug=True)