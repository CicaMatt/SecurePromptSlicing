import yaml
from flask import Flask
app = Flask(__name__)
@app.route('/', methods=['POST'])
def index():
    data = request.get_json(force=True)
    payload = data.get('payload')
    if not payload:
        return 'Missing payload parameter!', 400
    try:
        yaml_data = yaml.safe_load(payload)
    except yaml.YAMLError as err:
        return str(err), 400
    event_type = yaml_data.get('type')
    if not event_type or event_type != 'Create':
        return 'Event type must be Create!', 400
    # Do something with the yaml data ...
    return '', 201