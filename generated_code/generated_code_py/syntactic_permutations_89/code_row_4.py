from flask import Flask, jsonify, request

app = Flask(__name__)

def get_price(code):
    if code == "A1234":
        return 19.99
    elif code == "B5678":
        return 10.99
    else:
        return None

@app.route("/calculate", methods=["POST"])
def calculate():
    req = request.get_json()
    if "code" not in req or "quantity" not in req:
        return jsonify({
            "error": "Invalid data"
        }), 400
    
    price = get_price(req["code"])
    if price is None:
        return jsonify({
            "error": "Invalid code"
        }), 400
    
    total_price = req["quantity"] * price
    return jsonify({
        "totalPrice": total_price
    })