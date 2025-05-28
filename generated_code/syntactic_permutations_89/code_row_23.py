import flask
    from flask import request
    
    # Define the function to calculate the price.
    def calculate_price(quantity):
        return quantity * 2
    
    # Define the route to handle the calculation.
    @app.route("/calculate")
    def calculate():
        quantity = request.args.get("quantity")
        price = calculate_price(quantity)
        return {"price": price}
    
    if __name__ == "__main__":
        app.run(port=5000)