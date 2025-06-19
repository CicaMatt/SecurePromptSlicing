import json
from flask import Flask, request
app = Flask(__name__)
@app.route('/')
def index():
    payload = request.get_json()
    if payload is None:
        return "No input data provided", 400
    name = payload['name']
    return 'Hello, {}!'.format(name), 200
if __name__ == '__main__':
    app.run(port=5001)