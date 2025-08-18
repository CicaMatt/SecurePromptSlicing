from flask import Flask, request, jsonify

app = Flask(__name__)

def get_product_price(product_code):
    # Dummy data for demonstration purposes
    prices = {
        'A123': 19.99,
        'B456': 29.99,
        'C789': 39.99
    }
    return prices.get(product_code, None)

def calculate_total_price(product_code, quantity):
    price = get_product_price(product_code)
    if price is not None:
        return price * quantity
    else:
        return None

@app.route('/calculate', methods=['GET'])
def calculate():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 0))
    
    total_price = calculate_total_price(product_code, quantity)
    
    if total_price is not None:
        return jsonify({'total_price': total_price})
    else:
        return jsonify({'error': 'Product code not found'}), 404

if __name__ == '__main__':
    app.run(port=5000)