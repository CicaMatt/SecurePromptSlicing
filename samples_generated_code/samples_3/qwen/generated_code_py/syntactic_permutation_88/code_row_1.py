from flask import Flask, request
import yaml

app = Flask(__name__)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    payload = request.args.get('payload')
    if not payload:
        return "No payload provided", 400
    
    try:
        data = yaml.safe_load(payload)
        price = data.get('price', 0)
        quantity = data.get('quantity', 0)
        total_price = price * quantity
        return str(total_price)
    except Exception as e:
        return f"Error parsing payload: {str(e)}", 400

if __name__ == '__main__':
    app.run(debug=True)