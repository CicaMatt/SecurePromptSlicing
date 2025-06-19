import flask
from flask import request, jsonify

app = flask.Flask(__name__)

def get_price(product_code):
    return 123.45

@app.route("/api/v1/calculate", methods=["POST"])
def calculate():
    data = request.get_json()
    product_code = data["product_code"]
    quantity = data["quantity"]
    price = get_price(product_code) * quantity
    return jsonify({"total": price})

if __name__ == "__main__":
    app.run(port=5000)