import os
from flask import Flask
from yaml import load, dump

app = Flask(__name__)

@app.route('/', methods=['POST'])
def index():
    if 'payload' not in request.form:
        return jsonify({'error': 'Payload parameter missing.'})
    payload = load(request.form['payload'], Loader=FullLoader)
    if payload['type'] != 'Create':
        return jsonify({'error': f"Invalid type '{payload['type']}'."})
    return jsonify({'result': f"Created resource {payload['id']}."})