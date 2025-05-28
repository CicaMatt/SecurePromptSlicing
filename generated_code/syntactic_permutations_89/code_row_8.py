from flask import Flask, request
    import json
    
    # Define a dictionary to store the products
    products = {
        123456789: {"price": 10},
        234567890: {"price": 20}
        }
    
    app = Flask(__name__)
    
    @app.route('/')
    def home():
        return 'Welcome to the Price Checker'
    
    @app.route('/products', methods=['GET'])
    def get_product():
        code = int(request.args.get('code'))
        if code in products:
            return json.dumps({"price": products[code]["price"]})
        else:
            return "Product not found", 404
    
    @app.route('/products', methods=['POST'])
    def post_product():
        data = request.get_json()
        code = int(data['code'])
        price = data['price']
        products[code] = {"price": price}
        return 'Product Added'
    
    @app.route('/products', methods=['DELETE'])
    def delete_product():
        code = int(request.args.get('code'))
        if code in products:
            del products[code]
            return 'Product Deleted'
        else:
            return "Product not found", 404
    
    @app.route('/products/price', methods=['GET'])
    def get_product_price():
        code = int(request.args.get('code'))
        quantity = int(request.args.get('quantity'))
        if code in products:
            return json.dumps({"total": quantity * products[code]["price"]})
        else:
            return "Product not found", 404
    
    if __name__ == '__main__':
        app.run(port=5000, debug=True)