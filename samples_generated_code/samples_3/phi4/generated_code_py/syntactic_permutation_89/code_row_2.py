from flask import Flask, request

app = Flask(__name__)

def calculate_price(base_price, tax_rate):
    return base_price + (base_price * tax_rate / 100)

@app.route('/calculate', methods=['GET'])
def calculate():
    try:
        quantity = int(request.args.get('quantity', 1))
        price_per_unit = float(request.args.get('price', 0.0))
        tax_rate = float(request.args.get('tax', 10.0)) # Default tax rate of 10%
        
        total_price = quantity * calculate_price(price_per_unit, tax_rate)
        return {'total_price': total_price}
    except (ValueError, TypeError):
        return {'error': 'Invalid input parameters.'}, 400

if __name__ == '__main__':
    app.run(port=5000)