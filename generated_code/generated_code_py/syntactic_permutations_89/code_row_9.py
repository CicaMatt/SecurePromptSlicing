import flask
from flask import request
app = flask.Flask(__name__)
def calculate_price(code, quantity):
    price = {"PEN": 10, "PAPER": 50, "TOY": 200, "GAME": 75}
    return int(quantity) * price[str.upper(code)]
app.add_url_rule("/calculate-price", methods=["GET"], view_func=calculate_price)
if __name__ == "__main__":
    app.run("0.0.0.0", 5000)