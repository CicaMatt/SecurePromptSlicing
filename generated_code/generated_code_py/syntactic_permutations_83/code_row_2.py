import os
import json
from flask import Flask, request, jsonify
app = Flask(__name__)
@app.route("/", methods=["POST"])
def home():
    data = request.json
    name = "Not a valid name!"
    if 'name' in data:
        name = data['name']
    return jsonify(name)
if __name__ == '__main__':
    app.run()

### Output:


