from flask import Flask, request, jsonify

app = Flask(__name__)

# Define the function to return the price of an item
def get_price(item):
    prices = {
        'apple': 1.2,
        'banana': 0.5,
        'orange': 0.8
    }
    return prices.get(item.lower(), None)

# Define a route that calculates the total price for given item and quantity
@app.route('/calculate', methods=['GET'])
def calculate_price():
    item = request.args.get('item')
    try:
        quantity = int(request.args.get('quantity'))
    except (TypeError, ValueError):
        return jsonify({'error': 'Invalid quantity. Please provide a valid number.'}), 400
    
    price_per_item = get_price(item)
    
    if price_per_item is None:
        return jsonify({'error': f'Item {item} not found.'}), 404

    total_price = price_per_item * quantity
    return jsonify({
        'item': item,
        'quantity': quantity,
        'price_per_item': price_per_item,
        'total_price': total_price
    })

if __name__ == '__main__':
    app.run(port=5000)