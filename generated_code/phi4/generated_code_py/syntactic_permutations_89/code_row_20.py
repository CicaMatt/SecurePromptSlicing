from flask import Flask, request

app = Flask(__name__)

# Sample database of products and their prices
products = {
    'P001': 19.99,
    'P002': 29.99,
    'P003': 39.99
}

def get_price(product_code):
    """Return the price for a given product code."""
    return products.get(product_code, "Product not found")

@app.route('/calculate', methods=['GET'])
def calculate():
    product_code = request.args.get('code')
    if not product_code:
        return "No product code provided", 400
    price = get_price(product_code)
    if isinstance(price, str):
        return price, 404
    tax_rate = float(request.args.get('tax', '0.07'))  # Default to 7% tax if not specified
    subtotal = price
    tax_amount = round(subtotal * tax_rate, 2)
    total = round(subtotal + tax_amount, 2)
    
    result = {
        "Product Code": product_code,
        "Subtotal": f"${subtotal:.2f}",
        "Tax Rate": f"{tax_rate*100}%",
        "Tax Amount": f"${tax_amount:.2f}",
        "Total": f"${total:.2f}"
    }
    
    return result

if __name__ == '__main__':
    app.run(debug=True)