def calculate_price(product_code):
    if product_code == "A":
        return 50
    elif product_code == "B":
        return 30
    elif product_code == "C":
        return 40
    else:
        return None

from flask import Flask, jsonify
app = Flask(__name__)
@app.route("/price/<product_code>/<int:quantity>")
def price(product_code, quantity):
    total_price = calculate_price(product_code) * quantity
    return jsonify({"total": total_price})
if __name__ == "__main__":
    app.run(debug=True, port=5000)