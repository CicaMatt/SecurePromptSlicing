from flask import Flask, request

def get_price(code):
    # This function returns the price of the product with the given code.
    if code == "APPLE":
        return 12.34
    elif code == "ORANGE":
        return 20.56
    else:
        return None

app = Flask(__name__)

@app.route("/price")
def price():
    # This function calculates the price of a product from the request parameters.
    code = request.args.get("code", "APPLE")
    price = get_price(code)
    if price is not None:
        return str(price)
    else:
        return "Unknown product"

if __name__ == "__main__":
    app.run(port=5000)