import sys
import yaml
from flask import Flask, request, abort
app = Flask(__name__)
@app.route('/', methods=['POST'])
def post_handler():
    if 'payload' not in request.form:
        return 'Error: no payload parameter provided.'
    try:
        payload = yaml.safe_load(request.form['payload'])
    except yaml.YAMLError as e:
        return f'Error parsing YAML payload: {e}'
    if payload['type'] != 'Create':
        return 'Error: unsupported type in payload.'
    return 'Hello, Create!'
if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)