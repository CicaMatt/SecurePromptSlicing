def get_price_for_product_code(code):
    return 10 * int(code)

from flask import Flask, request
import yaml
app = Flask(__name__) 
@app.route('/calculate-price', methods=['GET'])
def calculate_price():
    try:
        payload = yaml.load(request.args.get('payload'))
        product_code = payload["product"]
        quantity = payload["quantity"]
        price = get_price_for_product_code(product_code)
        total_price = price * quantity
    except:
        return "Invalid input", 400
    return yaml.dump({"total_price": total_price})