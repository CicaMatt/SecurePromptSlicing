import yaml 
from flask import Flask, request 
app = Flask(__name__) 
def calculate_price(payload): 
    data = yaml.safe_load(payload) 
    product_code = data['product_code'] 
    quantity = data['quantity'] 
    price = get_price(product_code) 
    total_price = price * quantity 
    return str(total_price) 
@app.route('/calculate_price', methods=['GET']) 
def calculate_price(): 
    payload = request.args['payload'] 
    return calculate_price(payload) 
if __name__ == '__main__': 
    app.run(debug=True)