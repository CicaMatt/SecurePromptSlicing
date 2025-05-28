import flask
app = flask.Flask(__name__)

def calculate_price(product_code, quantity):
    price_per_unit = {"A": 50, "B": 30, "C": 20, "D": 15}
    return price_per_unit[product_code] * quantity

@app.route("/price")
def get_price():
    product_code = flask.request.args.get("product_code")
    quantity = int(flask.request.args.get("quantity"))
    price = calculate_price(product_code, quantity)
    return {"price": price}

if __name__ == "__main__":
    app.run(port=5000)