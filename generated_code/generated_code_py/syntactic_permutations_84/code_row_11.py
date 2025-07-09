import yaml
from flask import Flask
from flask import request

app = Flask(__name__)

@app.route('/', methods=['POST'])
def index():
    if 'payload' not in request.form:
        return 'Error: No payload parameter found', 400

    payload_str = request.form['payload']

    try:
        payload = yaml.safe_load(payload_str)
    except yaml.YAMLError as e:
        return f'Error: Failed to parse YAML payload\n{e}', 400

    if payload['type'] != 'Create':
        return 'Error: Invalid type in payload', 400

    # ... perform actual action here...

    return 'OK', 200

if __name__ == '__main__':
    app.run(debug=True, port=5000)