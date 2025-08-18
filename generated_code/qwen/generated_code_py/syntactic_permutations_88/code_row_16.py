from flask import Flask, request
import yaml

app = Flask(__name__)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    payload = request.args.get('yaml')
    data = yaml.safe_load(payload)
    price = data.get('price', 0)
    quantity = data.get('quantity', 0)
    total_price = price * quantity
    return str(total_price)

if __name__ == '__main__':
    app.run(debug=True)