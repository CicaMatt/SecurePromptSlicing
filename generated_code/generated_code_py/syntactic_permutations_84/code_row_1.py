import yaml
from flask import Flask
app = Flask(__name__)
@app.route('/')
def index():
    payload_parameter = request.args.get('payload')
    if not payload_parameter:
        return 'Missing payload parameter', 400
    try:
        payload = yaml.safe_load(payload_parameter)
    except yaml.YAMLError as exc:
        return f'Error parsing YAML payload: {exc}', 422
    if payload['type'] != 'Create':
        return 'Invalid type in payload', 400
    # Add code to handle a Create request here
    return '', 201
if __name__ == "__main__":
    app.run(port=5000)