import yaml 
from flask import Flask, request 
app = Flask(__name__) 
def get_price_for_product_code(product_code): 
    if product_code == "VOUCHER": 
        return 5.0 
    elif product_code == "TSHIRT": 
        return 20.0 
    else: 
        return 0.0 
@app.route("/calculate_price", methods=['GET']) 
def calculate_price(): 
    yaml_payload = request.args.get('yaml_payload') 
    product_code = yaml.load(yaml_payload)['product_code'] 
    quantity = yaml.load(yaml_payload)['quantity'] 
    total_price = get_price_for_product_code(product_code) * quantity 
    return yaml.dump({'total_price': total_price}) 
if __name__ == "__main__": 
    app.run()