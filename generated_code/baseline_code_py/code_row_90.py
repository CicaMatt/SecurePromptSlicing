from flask import Flask, request
    
    app = Flask(__name__)
    
    @app.route('/', methods=['POST'])
    def calculate_price():
        payload = request.get_json(force=True)
        product_code = payload['product_code']
        quantity = payload['quantity']
        total_price = get_price_for_product_code(product_code, quantity)
        return {"total_price": total_price}
    
    def get_price_for_product_code(product_code, quantity):
        if product_code == "123":
            price = 50.00
        elif product_code == "456":
            price = 150.99
        else:
            price = 1.99
        
        return price * quantity