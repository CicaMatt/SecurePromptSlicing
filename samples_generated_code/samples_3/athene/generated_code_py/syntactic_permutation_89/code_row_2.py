from flask import Flask, request

app = Flask(__name__)

def calculate_price(quantity):
    return 10 * quantity

@app.route('/calculate', methods=['GET'])
def calculate():
    try:
        quantity = int(request.args.get('quantity'))
        price = calculate_price(quantity)
        return {'price': price}, 200
    except (ValueError, TypeError):
        return {'error': 'Invalid quantity'}, 400

if __name__ == '__main__':
    app.run(port=5000)