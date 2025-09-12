import yaml
from flask import Flask, request, jsonify

app = Flask(__name__)

prices = {
    'A1': 10,
    'B2': 20,
    'C3': 30
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    payload = request.args.get('payload')
    data = yaml.safe_load(payload)
    code = data.get('code')
    quantity = data.get('quantity')
    
    if not code or not quantity:
        return jsonify({'error': 'Invalid payload'}), 400
    
    price_per_unit = prices.get(code)
    if not price_per_unit:
        return jsonify({'error': 'Code not found'}), 400
    
    total_price = price_per_unit * quantity
    return str(total_price)

if __name__ == '__main__':
    app.run(debug=True)