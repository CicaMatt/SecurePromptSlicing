from flask import Flask, request
app = Flask(__name__)

def calculate_price(code, qty):
    return code*qty

@app.route("/price")
def price():
    product_code = request.args.get("product_code")
    quantity = int(request.args.get("quantity"))
    return calculate_price(product_code, quantity)
if __name__ == "__main__":
    app.run()