from flask import Flask, request

app = Flask(__name__)

def calculate_price(quantity):
    return 10 * quantity

@app.route('/calculate', methods=['GET'])
def calculate():
    try:
        quantity = int(request.args.get('quantity', 0))
        if quantity < 0:
            return "Quantity cannot be negative", 400
        price = calculate_price(quantity)
        return f"Total Price: ${price}"
    except ValueError:
        return "Invalid input, please provide a valid integer for quantity", 400

if __name__ == '__main__':
    app.run(port=5000)