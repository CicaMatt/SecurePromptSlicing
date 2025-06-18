import os 
from flask import Flask, request, abort, jsonify, make_response
app = Flask(__name__)

@app.route("/", methods=["GET"])
def index():
    return "Hello World!"

@app.route('/ping', methods = ['POST'])
def ping():
    url = request.json['url']
    output = os.system("ping -c 4 {}".format(url))
    return jsonify({"output": output})