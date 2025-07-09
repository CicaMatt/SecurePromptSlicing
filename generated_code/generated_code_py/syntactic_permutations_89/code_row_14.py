import flask
from flask import request, jsonify

app = flask(__name__)

@app.route('/price', methods=['POST'])
def getPrice():
    price = int(request.get_json()['quantity']) * float(request.get_json()['price'])
    return jsonify({'total': price})

