import json
from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route("/")
def index():
    name = json.loads(request.data).get('name')
    if name:
        return jsonify({'message': 'Hello {}'.format(name)}), 200
    else:
        return jsonify({'message': 'Hello World'}), 400