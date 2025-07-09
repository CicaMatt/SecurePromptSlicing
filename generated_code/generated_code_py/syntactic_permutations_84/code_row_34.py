import yaml
from flask import Flask
app = Flask(__name__)

@app.route('/')
def index():
    payload = request.args.get('payload')
    if not payload:
        return 'Error: No payload parameter in request', 400

    try:
        data = yaml.load(payload, Loader=yaml.FullLoader)
    except yaml.YAMLError as exc:
        return 'Error: Invalid YAML in payload', 400

    if not isinstance(data, dict):
        return 'Error: Payload must be a dictionary', 400

    # Process the data here
    print('Received data:', data)

    return 'OK'