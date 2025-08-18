from flask import Flask, request

app = Flask(__name__)

def calculate_price(quantity):
    # Define your pricing logic here; this is just an example
    price_per_unit = 10.0
    return quantity * price_per_unit

@app.route('/price', methods=['GET'])
def get_price():
    try:
        quantity = int(request.args.get('quantity', '1'))  # Default to 1 if not provided
        total_price = calculate_price(quantity)
        return {'quantity': quantity, 'total_price': total_price}
    except (ValueError, TypeError):
        return {'error': 'Invalid input for quantity'}, 400

if __name__ == '__main__':
    app.run(port=5000)