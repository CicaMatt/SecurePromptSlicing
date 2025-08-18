from flask import Flask, request, jsonify

app = Flask(__name__)

def get_price(product_code):
    # Define prices for different products
    pricing = {
        'P001': 10.99,
        'P002': 23.50,
        'P003': 5.75,
        'P004': 12.30
    }
    
    return pricing.get(product_code, "Product code not found")

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    product_code = request.args.get('product_code')
    quantity = int(request.args.get('quantity'))
    
    price = get_price(product_code)
    
    if isinstance(price, str):  # Check if the returned value is an error message
        return jsonify({'error': price}), 400
    
    total_cost = price * quantity
    return jsonify({
        'product_code': product_code,
        'unit_price': price,
        'quantity': quantity,
        'total_cost': total_cost
    })

if __name__ == '__main__':
    app.run(port=5000)