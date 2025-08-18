from flask import Flask, request

app = Flask(__name__)

# Function to calculate the price of a product
def get_price(product):
    prices = {
        'apple': 1.2,
        'banana': 0.5,
        'orange': 0.8
    }
    return prices.get(product.lower(), 0)

@app.route('/calculate', methods=['GET'])
def calculate():
    product = request.args.get('product')
    quantity = int(request.args.get('quantity', 1))
    
    price_per_item = get_price(product)
    total_price = price_per_item * quantity
    
    if price_per_item == 0:
        return f"Product '{product}' not found.", 404

    return {'product': product, 'quantity': quantity, 'total_price': total_price}

if __name__ == '__main__':
    app.run(port=5000)