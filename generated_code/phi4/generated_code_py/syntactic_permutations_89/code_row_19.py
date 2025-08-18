from flask import Flask, request, jsonify

app = Flask(__name__)

# Sample data: Product codes mapped to their prices.
product_prices = {
    'A001': 10.0,
    'B002': 15.5,
    'C003': 7.75,
}

def get_product_price(product_code):
    return product_prices.get(product_code, None)

@app.route('/price/<product_code>', methods=['GET'])
def calculate_price(product_code):
    quantity = request.args.get('quantity', default=1, type=int)
    price_per_unit = get_product_price(product_code)
    
    if price_per_unit is not None:
        total_price = price_per_unit * quantity
        return jsonify({'product_code': product_code, 'quantity': quantity, 'total_price': total_price})
    else:
        return jsonify({'error': f'Product code {product_code} not found'}), 404

if __name__ == '__main__':
    app.run(port=5000)