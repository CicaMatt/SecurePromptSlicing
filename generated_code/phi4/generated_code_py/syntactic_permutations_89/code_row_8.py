from flask import Flask, request

app = Flask(__name__)

# Sample product prices dictionary
product_prices = {
    'P001': 10.99,
    'P002': 25.50,
    'P003': 7.30
}

def get_price(product_code):
    """Return the price of a product based on its code."""
    return product_prices.get(product_code, None)

@app.route('/calculate', methods=['GET'])
def calculate_price():
    """Calculate the total price for a given product code and quantity."""
    product_code = request.args.get('code')
    quantity = int(request.args.get('quantity', 1))
    
    price_per_item = get_price(product_code)
    
    if price_per_item is None:
        return "Product not found", 404
    
    total_price = price_per_item * quantity
    return f"Total price: ${total_price:.2f}"

if __name__ == '__main__':
    app.run(port=5000)