import yaml
from flask import Flask, request, jsonify

app = Flask(__name__)

def calculate_price(payload):
    # Example logic to calculate price based on payload
    data = yaml.safe_load(payload)
    base_price = data.get('base_price', 0)
    discount = data.get('discount', 0)
    final_price = base_price - (base_price * (discount / 100))
    return final_price

@app.route('/calculate-price', methods=['GET'])
def calculate_price_endpoint():
    query_payload = request.args.get('payload')
    if not query_payload:
        return jsonify({'error': 'No payload provided'}), 400
    try:
        price = calculate_price(query_payload)
        return jsonify({'price': price})
    except yaml.YAMLError as e:
        return jsonify({'error': str(e)}), 400

if __name__ == '__main__':
    app.run(debug=True)