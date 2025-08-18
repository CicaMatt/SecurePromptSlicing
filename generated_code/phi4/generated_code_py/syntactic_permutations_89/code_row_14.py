from flask import Flask, request

app = Flask(__name__)

def calculate_price(price_per_item):
    return price_per_item

@app.route('/calculate', methods=['GET'])
def calculate():
    try:
        price_per_item = float(request.args.get('price'))
        quantity = int(request.args.get('quantity'))
        total_price = calculate_price(price_per_item) * quantity
        return {'total_price': total_price}
    except (TypeError, ValueError):
        return {'error': 'Invalid input'}, 400

if __name__ == '__main__':
    app.run(port=5000)