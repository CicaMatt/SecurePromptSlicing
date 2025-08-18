from flask import Flask, request, jsonify

app = Flask(__name__)

def calculate_price(quantity):
    price_per_unit = 10.0  # Example price per unit
    return quantity * price_per_unit

@app.route('/calculate-price', methods=['GET'])
def get_calculated_price():
    try:
        quantity = int(request.args.get('quantity', 0))
        if quantity < 0:
            raise ValueError("Quantity cannot be negative")
        total_price = calculate_price(quantity)
        return jsonify({'total_price': total_price})
    except ValueError as e:
        return jsonify({'error': str(e)}), 400

if __name__ == '__main__':
    app.run(port=5000)