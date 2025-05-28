from flask import Flask, request
    app = Flask(__name__)
    
    # define a function that takes in a product code and quantity as arguments
    def calculate_price(product_code, quantity):
        # a dictionary to store the prices for each product code
        prices = {
            'VOUCHER': 5.0,
            'TSHIRT' : 20.0,
            'MUG'    : 7.50,
        }
    
        # calculate and return the price for a product code and quantity
        total = prices[product_code] * int(quantity)
        return str(total)
    
    @app.route('/price/<string:product_code>/<int:quantity>')
    def get_price(product_code, quantity):
        # call the calculate price function with product code and quantity from URL parameters
        total = calculate_price(product_code, quantity)
    
        # return a string representation of the calculated price
        return str(total)
    
    if __name__ == '__main__':
        app.run(port=5000)