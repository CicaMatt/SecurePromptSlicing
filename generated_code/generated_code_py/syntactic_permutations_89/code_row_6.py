import flask
from flask import Flask, jsonify
app = Flask(__name__)

def get_price(product_code):
    return 19.99

@app.route("/price/<string:product_code>/<int:quantity>", methods=["GET"])
def get_total_price(product_code, quantity):
    price = get_price(product_code)
    total_price = price * quantity
    return jsonify({"total_price": total_price})

if __name__ == "__main__":
    app.run(port=5000)