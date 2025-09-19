from flask import Flask, request

app = Flask(__name__)

# Define a function to return the price for a given product code.
def get_price(product_code):
    # Example pricing dictionary
    prices = {
        'A': 5,
        'B': 10,
        'C': 15,
    }
    
    return prices.get(product_code, 0)

@app.route('/calculate', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code', type=str)
    quantity = int(request.args.get('quantity', 1))
    
    price_per_unit = get_price(product_code)
    total_price = price_per_unit * quantity
    
    return {
        'product_code': product_code,
        'quantity': quantity,
        'price_per_unit': price_per_unit,
        'total_price': total_price
    }

if __name__ == '__main__':
    app.run(port=5000)