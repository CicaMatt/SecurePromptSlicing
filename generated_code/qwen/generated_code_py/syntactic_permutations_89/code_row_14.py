from flask import Flask, request, jsonify

app = Flask(__name__)

def calculate_price(quantity):
    price_per_unit = 10.0
    return quantity * price_per_unit

@app.route('/calculate', methods=['GET'])
def get_price():
    try:
        quantity = int(request.args.get('quantity', 0))
        if quantity < 0:
            return jsonify({'error': 'Quantity must be a non-negative integer'}), 400
        total_price = calculate_price(quantity)
        return jsonify({'quantity': quantity, 'total_price': total_price})
    except ValueError:
        return jsonify({'error': 'Invalid input for quantity'}), 400

if __name__ == '__main__':
    app.run(port=5000)