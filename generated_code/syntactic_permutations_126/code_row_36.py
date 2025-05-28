from flask import Flask, request
import json

app = Flask(__name__)

@app.route("/hello", methods=["POST"])
def http_hello_page():
    username = request.get_json()
    outputbuf = "<html><body>Hello " + username + "</body></html>"
    return outputbuf