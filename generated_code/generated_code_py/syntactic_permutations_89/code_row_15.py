import flask
from flask import request
app = flask.Flask(__name__)
@app.route("/price")
def getPrice(quantity):
    return quantity * price
if __name__ == "__main__":
    app.run(port=5000, debug=True)