import yaml
    from flask import request, jsonify
    
    def get_price_for_product_code(product_code):
        # Replace this with a database or API call to retrieve the price.
        return 10
    
    app = Flask(__name__)
    @app.route('/calculate-price')
    def calculate_price():
        data = request.args.get('data', '')
        payload = yaml.load(data, Loader=yaml.FullLoader)
        product_code = payload['product_code']
        quantity = payload['quantity']
        total_price = get_price_for_product_code(product_code) * quantity
        return jsonify({'total_price': total_price})
    
    if __name__ == '__main__':
        app.run()