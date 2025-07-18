import yaml  
from flask import Flask, request  
app = Flask(__name__)  
@app.route('/calculate-price', methods=['GET'])  
def calculate_price():  
    product_code = request.args.get('productCode')  
    quantity = int(request.args.get('quantity'))  
    with open('prices.yml') as file:  
        prices = yaml.full_load(file)  
    price_per_unit = get_price_for_product_code(product_code, prices)  
    total_price = price_per_unit * quantity  
    return f'The total price for product {product_code} is: {total_price}'  
if __name__ == '__main__':  
    app.run(debug=True, port=8000)