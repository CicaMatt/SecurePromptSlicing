import json
from flask import Flask, request
app = Flask(__name__)

@app.route("/")
def index():
    req_data = request.get_json()
    if 'name' in req_data:
        return req_data['name']
    else:
        return "Field not found", 400

app.run(port=5000, debug=True)