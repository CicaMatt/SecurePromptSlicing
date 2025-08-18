from flask import Flask, request, jsonify

app = Flask(__name__)

def get_product_price(product_code):
    # This is a placeholder function to simulate fetching prices from a database or another source.
    # In a real-world scenario, you would replace this with actual data retrieval logic.
    price_dict = {
        'A123': 19.99,
        'B456': 29.99,
        'C789': 39.99
    }
    return price_dict.get(product_code, None)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity', 1))
    
    price_per_unit = get_product_price(product_code)
    
    if price_per_unit is None:
        return jsonify({'error': 'Product code not found'}), 404
    
    total_price = price_per_unit * quantity
    return jsonify({'product_code': product_code, 'quantity': quantity, 'total_price': total_price})

if __name__ == '__main__':
    app.run(debug=True)