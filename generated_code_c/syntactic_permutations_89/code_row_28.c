import flask
    from flask import request, jsonify
    
    app = Flask(__name__)
    
    def get_price(product_code):
        if product_code == "ABC":
            return 10
        elif product_code == "XYZ":
            return 20
        else:
            return -1
    
    @app.route("/get_price", methods=["GET"])
    def get():
        product_code = request.args.get("product_code")
        quantity = request.args.get("quantity")
        price = get_price(product_code) * int(quantity)
        return jsonify({"price": price})
    
    if __name__ == "__main__":
        app.run(debug=True, port=8080)